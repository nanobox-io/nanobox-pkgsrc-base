#!/bin/bash

detect_platform() {
  if [ $(uname | grep 'SunOS') ]; then
    echo "SmartOS"
  elif [ $(uname | grep 'Linux') ]; then
    echo "Linux"
  fi    
}

project='base'
platform=$(detect_platform)
depends=(
  net/libfetch
  )
packages=(
  devel/bmake
  pkgtools/bootstrap-mk-files
  archivers/bzip2
  sysutils/coreutils
  devel/gettext-lib
  archivers/libarchive
  security/mozilla-rootcerts
  lang/nawk
  textproc/nbsed
  devel/ncurses
  security/openssl
  pkgtools/pkg_alternatives
  pkgtools/pkg_install
  pkgtools/pkg_install-info
  pkgtools/pkgin
  devel/readline
  databases/sqlite3
  archivers/xz
  devel/zlib
  )
extra_packages=(
  pkgtools/mksandbox
  )

# 0) clean start
sudo rm -rf /data
sudo rm -rf /var/tmp/${project}-bootstrap
# sudo rm -rf /content/packages/pkgsrc/data/Linux

# 1) install build-essential
sudo apt-get -y update -qq && \
sudo apt-get install -y build-essential

# 2) run bootstrap process
sudo GCCBASE=/usr \
  SH=/bin/bash \
  /content/pkgsrc/bootstrap/bootstrap \
  --compiler=gcc \
  --abi 64 \
  --full \
  --prefer-pkgsrc=yes \
  --pkgdbdir=/data/pkg \
  --prefix=/data \
  --varbase=/data/var \
  --workdir=/var/tmp/${project}-bootstrap

# 3) generate mk.conf
sudo bash -c "/bin/cat > /data/etc/mk.conf" <<END
.ifdef BSD_PKG_MK # begin pkgsrc settings

ABI=      64
PKGSRC_COMPILER=  gcc
GCCBASE=    /usr

PKG_DBDIR=    /data/pkg
LOCALBASE=    /data
VARBASE=    /data/var
PKG_TOOLS_BIN=    /data/sbin
PKGINFODIR=   info
PKGMANDIR=    man
DEPENDS_TARGET=   bin-install

PREFER_PKGSRC=    yes

TOOLS_PLATFORM.install?=  /data/bin/install-sh
TOOLS_PLATFORM.sh?=   /data/bin/pdksh
TOOLS_PLATFORM.ksh?=    /data/bin/pdksh
TOOLS_PLATFORM.awk?=    /data/bin/nawk
TOOLS_PLATFORM.sed?=    /data/bin/nbsed
TOOLS_PLATFORM.sh?=   /bin/bash

DISTDIR=      /content/distfiles
PACKAGES=     /content/packages/pkgsrc/${project}/Linux

WRKOBJDIR=      /var/tmp/pkgsrc-build-${project}

MAKE_JOBS=      6

SU_CMD=       sudo sh -c

LDFLAGS+=     -L/lib/x86_64-linux-gnu
LDFLAGS+=     -L/usr/lib/x86_64-linux-gnu
CFLAGS+=      -I/usr/include/x86_64-linux-gnu

ALLOW_VULNERABLE_PACKAGES=    yes
SKIP_LICENSE_CHECK=        yes
FETCH_USING=            curl

.endif      # end pkgsrc settings
END

# 4) make a tempoary tarball of the minimal bootstrap
sudo tar -czf /var/tmp/bootstrap.minimal.tar.gz -C / data

# 5) build and install dependencies
for i in ${depends[@]}; do
  /data/bin/bmake -C /content/pkgsrc/${i} package
  /data/bin/bmake -C /content/pkgsrc/${i} install
done

# 6) create extra necessary packages
for i in ${packages[@]}; do
  /data/bin/bmake -C /content/pkgsrc/${i} package
done

# 7) blast /data
sudo rm -rf /data

# 8) extract minimal bootstrap
sudo tar -xzf /var/tmp/bootstrap.minimal.tar.gz -C /

# 9) install the packages we just built
for i in ${packages[@]}; do
  pkg_name=$(/data/bin/bmake -C /content/pkgsrc/${i} show-var VARNAME=PKGNAME)
  sudo /data/sbin/pkg_add /content/packages/pkgsrc/${project}/Linux/All/${pkg_name}.tgz
done

# 10) tar
sudo tar -czf /var/tmp/bootstrap.tar.gz -C / data

# 11) upload
curl \
  -k \
  -X POST \
  -H "Key: ${NANOBOX_SECRET}" \
  --data-binary \@/var/tmp/bootstrap.tar.gz \
  https://pkgsrc.nanobox.io/${NANOBOX_USER}/${project}/${platform}/bootstrap.tar.gz

# 12) build/install extra packages
for i in ${extra_packages[@]}; do
  /data/bin/bmake -C /content/pkgsrc/${i} package
  /data/bin/bmake -C /content/pkgsrc/${i} install
done
