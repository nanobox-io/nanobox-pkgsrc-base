#!/bin/bash
# -*- mode: bash; tab-width: 2; -*-
# vim: ts=2 sw=8 ft=bash noet

# A utility to create isolated pkgsrc bootstrap environments to ensure
# package creation is isolated

# $1 = subcommand
# $2 = sandbox name

print_usage() {
  cat <<END
sandbox is a utility for generating isolated chroot environments
to build pkgsrc packages without leaking dependencies.

Usage: sandbox <command> [NAME]

where <command> is one of: up, enter, resume, rm, list
END
}

detect_platform() {
  if [ $(uname | grep 'SunOS') ]; then
    echo "SmartOS"
  elif [ $(uname | grep 'Linux') ]; then
    echo "Linux"
  fi    
}

create_chroot() {
  chroot=$1
  user=$(whoami)
  group=$(id -g -n ${user})
  project="base"
  platform=$(detect_platform)

  # ensure chroot dir exist
  sudo mkdir -p /chroot

  # make the chroot
  sudo \
    /data/sbin/mksandbox \
      --without-pkgsrc \
      --rwdirs=/run,/content,/home,/var/.ssh,/content/pkgsrc,/content/pkgsrc/base,/content/packages,/content/distfiles \
      /chroot/${chroot}

  sudo \
    /chroot/${chroot}/sandbox \
      chmod 777 /dev/shm

  sudo \
    /chroot/${chroot}/sandbox \
      chmod +t /dev/shm

  # copy ssh keys
  sudo \
    /chroot/${chroot}/sandbox \
      cp -f /var/.ssh/id_rsa /home/${user}/.ssh/id_rsa; \
      cp -f /var/.ssh/id_rsa.pub /home/${user}/.ssh/id_rsa.pub;

  # chown the ssh keys
  sudo \
    /chroot/${chroot}/sandbox \
      chown ${user}:${user} /home/${user}/.ssh/id_rsa; \
      chown ${user}:${user} /home/${user}/.ssh/id_rsa.pub;

  # create the pkgsrc file cache
  if [ ! -d /content/packages/pkgsrc/${project}/${platform} ]; then
    mkdir -p /content/packages/pkgsrc/${project}/${platform}
  fi

  # fetch bootstrap
  if [ ! -f /content/packages/pkgsrc/${project}/${platform}/bootstrap.tar.gz ]; then
    wget \
      http://pkgsrc.nanobox.io/nanobox/${project}/${platform}/bootstrap.tar.gz \
      -O /content/packages/pkgsrc/${project}/${platform}/bootstrap.tar.gz
  fi

  # extract bootstrap
  sudo \
    tar \
      -xz \
      -f /content/packages/pkgsrc/${project}/${platform}/bootstrap.tar.gz \
      -C /chroot/${chroot}

  # ensure /data/var/db/pkgin exists
  if [ ! -d /chroot/${chroot}/data/var/db/pkgin ]; then
    sudo mkdir -p /chroot/${chroot}/data/var/db/pkgin
  fi

  # ensure the platform dir exists
  if [ ! -d /content/packages/pkgsrc/${project}/${platform}/All ]; then
    sudo mkdir -p /content/packages/pkgsrc/${project}/${platform}/All
  fi

  # link /data/var/db/pkgin/cache to package dir
  if [ ! -L /chroot/${chroot}/data/var/db/pkgin/cache ]; then
    sudo ln -s /content/packages/pkgsrc/${project}/${platform}/All /chroot/${chroot}/data/var/db/pkgin/cache
  fi

  # link /etc/ssl/certs to the pkgin certs
  if [ ! -L /chroot/${chroot}/data/etc/openssl/certs ]; then
    sudo rm -rf /chroot/${chroot}/data/etc/openssl/certs
    sudo ln -s /etc/ssl/certs /chroot/${chroot}/data/etc/openssl/certs
  fi

  # chown /data directory
  echo "chown-ing /data directory"
  sudo \
    /chroot/${chroot}/sandbox \
      chown -R ${user}:${group} /data
}

enter_chroot() {
  chroot=$1
  user=`whoami`
  sudo \
    /chroot/${chroot}/sandbox \
      /bin/su \
        - \
        ${user}
}

remove_chroot() {
  chroot=$1
  if [[ -d /chroot/${chroot} ]]
  then
    if [ ! $(mount | grep -c ${chroot}/) = "0" ]
    then
      sudo /chroot/${chroot}/sandbox umount
    fi
    if [ $(mount | grep -c ${chroot}/) = "0" ]
    then
      sudo rm -rf /chroot/${chroot}
    fi
  fi
}

resume_chroot() {
  chroot=$1
  sudo /chroot/${chroot}/sandbox mount
}

list_chroots() {
  echo "CHROOTS:"
  for chroot in $(ls /chroot/); do
    echo "+> ${chroot}"
  done
}

# validate 2 args
# if [ ! $# = 2 ]; then
#   print_usage
#   exit 1
# fi

cmd=$1
name=$2

case $cmd in
  "up"|"create" )
    create_chroot $name
    echo "$name created"
    ;;
  "enter" )
    enter_chroot $name
    ;;
  "rm" )
    remove_chroot $name
    echo "$name destroyed"
    ;;
  "resume" )
    resume_chroot $name
    echo "$name resumed"
    ;;
  "list" )
    list_chroots
    ;;
  * )
    print_usage
    exit 1
    ;;
esac
