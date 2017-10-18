# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

VERSION=		2.3.6

DISTNAME=		rethinkdb-${VERSION}
CATEGORIES=		pagoda
MASTER_SITES=	https://download.rethinkdb.com/dist/
EXTRACT_SUFX=	.tgz

USE_TOOLS+=	gsed gmake perl
USE_LANGUAGES+=	c c++

HAS_CONFIGURE=		YES
CONFIG_SHELL=	bash

#MAKE_JOBS_SAFE=		no

#CONFIGURE_ARGS=		--lib-path ${PREFIX}/lib
CONFIGURE_ARGS+=	--allow-fetch
CONFIGURE_ARGS+=	--prefix ${PREFIX}
CONFIGURE_ARGS+=	--sysconfdir ${PKG_SYSCONFDIR:Q}
CONFIGURE_ARGS+=	--localstatedir ${VARBASE:Q}

CFLAGS+=	-Wno-error=unused-parameter
CFLAGS+=	-Wno-error=switch-enum

CXXFLAGS+=	-I${PREFIX}/include

LIBS+=		-pthread

pre-configure:
	echo ${CONFIGURE_ARGS}

DEPENDS+=	python>=2.7<=28:../../lang/python27
DEPENDS+=	nodejs>=0.10:../../base/nodejs010
BUILD_DEPENDS+=	m4>=1.4.17:../../devel/m4

#.include "../../devel/protobuf/buildlink3.mk"
.include "../../devel/jemalloc/buildlink3.mk"
#.include "../../devel/re2/buildlink3.mk"
#.include "../../www/curl/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
#.include "../../textproc/icu/buildlink3.mk"
.include "../../lang/python/tool.mk"
#.include "../../devel/boost-libs/buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
