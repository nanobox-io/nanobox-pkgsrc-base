#!/bin/bash

# A utility to create isolated pkgsrc bootstrap environments to ensure
# package creation is isolated

# $1 = subcommand
# $2 = sandbox name

print_usage() {
  cat <<END
sandbox is a utility for generating isolated chroot environments
to build pkgsrc packages without leaking dependencies.

Usage: sandbox <command> [NAME]

where <command> is one of: up, enter, rm, list
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
  project="base"
  platform=$(detect_platform)

  # ensure chroot dir exist
  sudo mkdir -p /chroot

  # make the chroot
  sudo \
    /data/sbin/mksandbox \
      --without-pkgsrc \
      --rwdirs=/content,/home,/content/pkgsrc,/content/pkgsrc/base,/content/packages,/content/distfiles \
      /chroot/${chroot}

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
  "up" )
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
  "list" )
    list_chroots
    ;;
  * )
    print_usage
    exit 1
    ;;
esac