# $NetBSD: Makefile,v 1.20 2013/09/20 06:30:02 jperkin Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
#  # vim: ts=8 sw=8 ft=make noet

DISTNAME=		serf-1.3.8
VERSION=		1.3.8
CATEGORIES=		www
MASTER_SITES=		https://archive.apache.org/dist/serf/
EXTRACT_SUFX=		.tar.bz2

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://code.google.com/p/serf/
COMMENT=		High-performance asynchronous HTTP client library
LICENSE=		apache-2.0

BUILD_DEPENDS+=		scons>=2.3.0:../../devel/scons

SCONS_ARGS+=		APR=${PREFIX}/bin/apr-1-config
SCONS_ARGS+=		APU=${PREFIX}/bin/apu-1-config
SCONS_ARGS+=		CC=${CC:Q}
SCONS_ARGS+=		CFLAGS=${CFLAGS:Q}
SCONS_ARGS+=		OPENSSL=${PREFIX}/lib

CFLAGS.SunOS+=		-D__EXTENSIONS__

do-build:
	cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${PREFIX}/bin/scons PREFIX=${PREFIX} ${SCONS_ARGS}

do-install:
	cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${PREFIX}/bin/scons PREFIX=${DESTDIR}${PREFIX} ${SCONS_ARGS} install

.include "../../base/apr/buildlink3.mk"
.include "../../base/apr-util/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
