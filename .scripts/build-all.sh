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

  # skip files
  if [ -f /content/pkgsrc/base/${package} ]; then
    continue
  fi

  if [[ "${package}" =~ "flip" ]]; then
    echo "can't build luvit"
    continue
  fi

  if [[ "${package}" =~ "apache24" ]]; then
    echo "can't build apache24"
    continue
  fi

  if [[ "${package}" =~ "kaffe" ]]; then
    echo "don't build kaffe"
    continue
  fi

  if [[ "${package}" =~ "jruby" ]]; then
    echo "don't build jruby"
    continue
  fi

  if [[ "${package}" =~ "mariadb" ]]; then
    echo "don't build mariadb"
    continue
  fi

  if [[ "${package}" =~ "percona" ]]; then
    echo "don't build percona"
    continue
  fi

  if [[ "${package}" =~ "xtrabackup" ]]; then
    echo "don't build xtrabackup"
    continue
  fi

  if [[ "${package}" =~ "openjdk" ]]; then
    echo "don't build openjdk yet"
    continue
  fi

  if [[ "${package}" =~ "luvit" ]]; then
    echo "gitorious is down"
    continue
  fi

  if [[ "${package}" =~ "redundis" ]]; then
    echo "luvit doesn't work"
    continue
  fi

  # skip java*
  if [[ "${package}" =~ "java-" ]]; then
    echo "ignoring ${package} because it's a java package"
    continue
  fi

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

  # ignore if it's a lib, other things will build them
  # also, some are only needed on certain OS's
  if [[ "${package}" =~ "lib" ]]; then
    echo "ignoring ${package} because it's a library"
    continue
  fi

  # ignore ruby common
  if [[ "${package}" = "ruby" ]]; then
    echo "ignoring ruby common"
    continue
  fi

  # ignore hhvm, it doesn't build yet
  if [[ "${package}" = "hhvm" ]]; then
    echo "ignoring hhvm"
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

  # ignore php 7.0 for now...
  if [[ "${package}" = "php70" ]]; then
    echo "ignoring php70 for the time being"
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
    "/data/bin/bmake -C /content/pkgsrc/base/${package} fetch-depends"
  if [ ! -f /content/packages/pkgsrc/base/Linux/All/${pkg_name}.tgz ]; then
    run_in_chroot \
      ${package} \
      "/data/bin/bmake -C /content/pkgsrc/base/${package} package"
  fi

  # 3) compile extensions or plugins if available
  if [[ "${package}" =~ "php" ]]; then
    php_version=${package/php/}
    bundle_pkg_name=$(/data/bin/bmake -C /content/pkgsrc/base/php-bundle show-var VARNAME=PKGNAME PHP_VERSION_DEFAULT=${php_version})
    run_in_chroot \
      ${package} \
      "/data/bin/bmake \
        -C /content/pkgsrc/base/php-bundle \
        fetch-depends \
        PHP_VERSION_DEFAULT=${php_version}"
    if [ ! -f /content/packages/pkgsrc/base/Linux/All/${bundle_pkg_name}.tgz ]; then
      run_in_chroot \
        ${package} \
        "/data/bin/bmake \
          -C /content/pkgsrc/base/php-bundle \
          package \
          PHP_VERSION_DEFAULT=${php_version}"
    fi
  elif [[ "${package}" =~ "ruby" ]]; then
    ruby_version=${package}
    for gem in $(ls /content/pkgsrc/base | grep -e 'ruby-'); do
      gem_pkg_name=$(/data/bin/bmake -C /content/pkgsrc/base/${gem} show-var VARNAME=PKGNAME RUBY_VERSION_SUPPORTED=${ruby_version})
      run_in_chroot \
        ${package} \
        "/data/bin/bmake \
          -C /content/pkgsrc/base/${gem} \
          fetch-depends \
          RUBY_VERSION_SUPPORTED=${ruby_version}"
      if [ ! -f /content/packages/pkgsrc/base/Linux/All/${gem_pkg_name}.tgz ]; then
        run_in_chroot \
          ${package} \
          "/data/bin/bmake \
            -C /content/pkgsrc/base/${gem} \
            package \
            RUBY_VERSION_SUPPORTED=${ruby_version}"
      fi
    done
  elif [[ "${package}" =~ "apache" ]]; then
    apache_version=${package}
    for extension in $(ls /content/pkgsrc/base | grep -e 'ap2?-'); do
      extension_pkg_name=$(/data/bin/bmake -C /content/pkgsrc/base/${extension} show-var VARNAME=PKGNAME PKG_APACHE_DEFAULT=${apache_version})
      run_in_chroot \
        ${package} \
        "/data/bin/bmake \
          -C /content/pkgsrc/base/${extension} \
          fetch-depends \
          PKG_APACHE_DEFAULT=${apache_version}"
      if [ ! -f /content/packages/pkgsrc/base/Linux/All/${extension_pkg_name}.tgz ]; then
        run_in_chroot \
          ${package} \
          "/data/bin/bmake \
            -C /content/pkgsrc/base/${extension} \
            package \
            PKG_APACHE_DEFAULT=${apache_version}"
      fi
    done
  elif [[ "${package}" =~ "jdk" ]]; then
    java_version=${package}
    for java in $(ls /content/pkgsrc/base | grep -e 'java-'); do
      java_pkg_name=$(/data/bin/bmake -C /content/pkgsrc/base/${java} show-var VARNAME=PKGNAME PKG_JVM_DEFAULT=${java_version})
      run_in_chroot \
        ${package} \
        "/data/bin/bmake \
          -C /content/pkgsrc/base/${java} \
          fetch-depends \
          PKG_JVM_DEFAULT=${java_version}"
      if [ ! -f /content/packages/pkgsrc/base/Linux/All/${java_pkg_name}.tgz ]; then
        run_in_chroot \
          ${package} \
          "/data/bin/bmake \
            -C /content/pkgsrc/base/${java} \
            package \
            PKG_JVM_DEFAULT=${java_version}"
      fi
    done
  fi

  # 4) cleanup chroot
  sandbox rm ${package}
done

# publish everything
/data/bin/bmake \
  -C /content/pkgsrc/base/apache22 \
  publish
