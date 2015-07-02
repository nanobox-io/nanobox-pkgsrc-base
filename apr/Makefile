# $NetBSD: Makefile,v 1.71 2013/07/04 16:24:02 wiz Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
#  # vim: ts=8 sw=8 ft=make noet

DISTNAME=		apr-${VERSION}
VERSION=		1.5.2
CATEGORIES=		devel
MASTER_SITES=		${MASTER_SITE_APACHE:=apr/}
EXTRACT_SUFX=		.tar.bz2

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://apr.apache.org/
COMMENT=		Apache Portable Runtime
LICENSE=		apache-2.0

PKG_INSTALLATION_TYPES=	overwrite pkgviews

USE_LIBTOOL=		yes
USE_MULTIARCH=		bin lib
USE_TOOLS+=		pkg-config
PKGCONFIG_OVERRIDE+=	apr.pc.in
GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--with-devrandom=/dev/urandom
CONFIGURE_ARGS+=	--with-installbuilddir=${PREFIX}/libexec${LIBARCHSUFFIX}/apr
CONFIGURE_ENV+=		LIBS=${LIBS:M*:Q}
LIBS.SunOS+=		-lnsl

MULTIARCH_DIRS.lib=	lib libexec

# XXX: why is this required for multiarch?
CHECK_INTERPRETER_SKIP+=	lib/*.exp

TEST_TARGET=		check

post-install:
	${RM} ${DESTDIR}${PREFIX}/libexec${LIBARCHSUFFIX}/apr/libtool
	${INSTALL_SCRIPT} ${PKG_LIBTOOL} ${DESTDIR}${PREFIX}/libexec${LIBARCHSUFFIX}/apr/libtool

.include "../../mk/bsd.prefs.mk"
.if ${OPSYS} == "Linux" || ${OPSYS} == "SunOS"
.include "../../devel/libuuid/buildlink3.mk"
.endif
.include "../../mk/bsd.pkg.mk"
