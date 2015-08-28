# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

# Requires libcap-dev to be installed

VERSION=		3.9.0
DISTNAME=		hhvm-${VERSION}
CATEGORIES=		pagoda
MASTER_SITES=		http://bitbucket.org/pagodaboxgrid/hhvm

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://github.com/facebook/hhvm
COMMENT=		HipHop Virtual Machine
LICENSE=       		PHP Zend

USE_TOOLS+= 		aclocal autoconf automake cmake libtool perl gawk gmake
USE_LANGUAGES+=		c c++ ocaml
USE_CMAKE=		yes

WRKSRC=			${WRKDIR}/hhvm

TOOLS_PATH.gawk=	/data/bin/gawk
TOOLS_PATH.awk=		/data/bin/gawk

GIT_REPOSITORIES=	hhvm
GIT_REPO.hhvm=		git@github.com:facebook/hhvm.git
GIT_TAG=		HHVM-${VERSION}
CMAKE_ARGS+=		-DLIBELF_INCLUDE_DIRS=/data/include/libelf
CMAKE_ARGS+=		-DLIBDWARF_INCLUDE_DIRS=/data/include
CMAKE_ARGS+=		-DLIBPNG_INCLUDE_DIRS=/data/include/libpng16
CMAKE_ARGS+=		-DLIBVPX_INCLUDE_DIRS=/data/include/vpx
CMAKE_ARGS+=		-DPCRE_INCLUDE_DIR=/data/include
CMAKE_ARGS+=		-DFRIBIDI_INCLUDE_DIR=/data/include
CMAKE_ARGS+=		-DENABLE_COTIRE=ON
CMAKE_ARGS+=		-DCMAKE_BUILD_TYPE=Release
#   -DMYSQL_UNIX_SOCK_ADDR=/path/to/mysql.socket
CMAKE_ARGS+=		-DMYSQL_UNIX_SOCK_ADDR=/dev/null
CMAKE_ARGS+=		-DLIBPNG_INCLUDE_DIR=/data/include
CMAKE_ARGS+=		-DWITH_SSL=/data
CMAKE_ARGS+=		-DMYSQL_INCLUDE_DIR=/data/include

EDITLINE_SKIP_FNAME_TRANSFORM=	yes

.include "../../base/git/git-package.mk"

# buildlinks
.include "../../archivers/bzip2/buildlink3.mk"
.include "../../archivers/libzip/buildlink3.mk"
.include "../../archivers/lz4/buildlink3.mk"
.include "../../base/gperftools/buildlink3.mk"
.include "../../base/libdwarf/buildlink3.mk"
.include "../../base/mysql/mysql.buildlink3.mk"
.include "../../converters/fribidi/buildlink3.mk"
.include "../../databases/openldap-client/buildlink3.mk"
.include "../../databases/sqlite/buildlink3.mk"
.include "../../databases/unixodbc/buildlink3.mk"
.include "../../devel/boost-libs/buildlink3.mk"
.include "../../devel/boost-headers/buildlink3.mk"
.include "../../devel/editline/buildlink3.mk"
.include "../../devel/google-glog/buildlink3.mk"
.include "../../devel/gmp/buildlink3.mk"
.include "../../devel/gperf/buildlink3.mk"
.include "../../devel/libelf/buildlink3.mk"
.include "../../devel/libevent/buildlink3.mk"
.include "../../devel/libiberty/buildlink3.mk"
.include "../../devel/libmemcached/buildlink3.mk"
.include "../../devel/libthrift/buildlink3.mk"
.include "../../devel/ncurses/buildlink3.mk"
.include "../../devel/pcre/buildlink3.mk"
.include "../../devel/readline/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../graphics/gd/buildlink3.mk"
.include "../../graphics/ImageMagick/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../lang/ocaml/buildlink3.mk"
# .include "../../mk/krb5.buildlink3.mk"
.include "../../multimedia/libvpx/buildlink3.mk"
.include "../../parallel/threadingbuildingblocks/buildlink3.mk"
.include "../../security/libmcrypt/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../textproc/expat/buildlink3.mk"
.include "../../textproc/icu/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../textproc/libxslt/buildlink3.mk"
.include "../../textproc/libyaml/buildlink3.mk"
.include "../../textproc/oniguruma/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"

.include "../../mk/bsd.pkg.mk"
