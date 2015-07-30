#!/bin/bash

set -e

run_in_chroot() {
  chroot=$1
  cmd=$2
  user=`whoami`
  sudo \
    /chroot/${chroot}/sandbox \
      /bin/su \
        - \
        ${user} \
        -c "${cmd}"
}

for package in $(ls /content/pkgsrc/base); do

  # ignore if it's not a real package
  if [ ! -f /content/pkgsrc/base/${package}/Makefile ]; then
    echo "ignoring ${package} because it does not have a Makefile"
    continue
  fi

  # ignore if it's a php extension
  if [[ "${package}" =~ "php-" ]]; then
    echo "ignoring ${package} because it's a php extension"
    continue
  fi

  # ignore ruby common
  if [[ "${package}" = "ruby" ]]; then
    echo "ignoring ruby common"
    continue
  fi

  # ignore if it's a rubygem
  if [[ "${package}" =~ "ruby-" ]]; then
    echo "ignoring ${package} because it's a rubygem"
    continue
  fi

  # ignore if it's an apache package
  if [[ "${package}" =~ "ap-" ]]; then
    echo "ignoring ${package} because it's an apache extension"
    continue
  fi

  # ignore if it's an apache package
  if [[ "${package}" =~ "ap2-" ]]; then
    echo "ignoring ${package} because it's an apache extension"
    continue
  fi

  # ignore apache 2.4 for now...
  if [[ "${package}" = "apache24" ]]; then
    echo "ignoring apache24 for the time being"
    continue
  fi

  if [[ "${package}" = "composer" ]]; then
    echo "ignoring composer for the time being"
    continue
  fi

  if [[ "${package}" = "galera" ]]; then
    echo "ignoring galera for now"
    continue
  fi

  if [[ "${package}" = "librpcsoc" ]]; then
    echo "ignoring librpcsoc because the source doesn't exist"
    continue
  fi

  if [[ "${package}" =~ "mariadb" ]]; then
    echo "skipping mariadb for now because it doesn't build"
    continue
  fi

  if [[ "${package}" =~ "ruby19" ]]; then
    echo "skipping ruby19 for now because it doesn't build"
    continue
  fi

  if [[ "${package}" =~ "percona-galera" ]]; then
    echo "skipping ${package} because it doesn't make sense for nanobox"
    continue
  fi

  # skip if package is already built
  pkg_name=$(/data/bin/bmake -C /content/pkgsrc/base/${package} show-var VARNAME=PKGNAME)
  if [ -f /content/packages/pkgsrc/base/Linux/All/${pkg_name}.tgz ]; then
    echo "skipping ${package} as it's already built"

    # cleaning cruft
    if [ -d /chroot/${package} ]; then
      sandbox rm ${package}
    fi

    continue
  fi

  # 1) create a chroot
  if [ ! -d /chroot/${package} ]; then
    sandbox create ${package}
  fi

  # 2) make package
  run_in_chroot \
    ${package} \
    "/data/bin/bmake -C /content/pkgsrc/base/${package} package"

  # 3) compile extensions or plugins if available
  if [[ "${package}" =~ "php" ]]; then
    php_version=${package/php/}
    run_in_chroot \
      ${package} \
      "/data/bin/bmake \
        -C /content/pkgsrc/base/php-bundle \
        package \
        PHP_VERSION_DEFAULT=${php_version}"
  elif [[ "${package}" =~ "ruby" ]]; then
    ruby_version=${package/ruby/}
    for gem in $(ls /content/pkgsrc/base | grep -e 'ruby-'); do
      run_in_chroot \
        ${package} \
        "/data/bin/bmake \
          -C /content/pkgsrc/base/${gem} \
          package \
          RUBY_VERSION_SUPPORTED=${ruby_version}"
    done
  elif [[ "${package}" =~ "apache" ]]; then
    apache_version=${package/apache/}
    for extension in $(ls /content/pkgsrc/base | grep -e 'ap2?-'); do
      run_in_chroot \
        ${package} \
        "/data/bin/bmake \
          -C /content/pkgsrc/base/${extension} \
          package \
          PKG_APACHE_DEFAULT=${apache_version}"
    done
  fi

  # 4) cleanup chroot
  sandbox rm ${package}
done

# publish everything
/data/bin/bmake \
  -C /content/pkgsrc/base/apache22 \
  publish
