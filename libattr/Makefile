# $NetBSD: Makefile,v 1.2 2014/05/29 23:35:35 wiz Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

VERSION=	2.4.47
DISTNAME=	attr-${VERSION}.src
# PKGREVISION=	1
PKGNAME=	libattr-${VERSION}
CATEGORIES=	devel
MASTER_SITES=	http://download.savannah.gnu.org/releases/attr/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://savannah.nongnu.org/projects/attr
COMMENT=	Commands for Manipulating Filesystem Extended Attributes
LICENSE=	GPL2

USE_TOOLS+=	gmake

GNU_CONFIGURE=	yes
USE_LANGUAGES=	c c++

OVERRIDE_DIRDEPTH.install-sh= -1
OVERRIDE_DIRDEPTH.libtool= -1

BUILD_TARGET=
INSTALL_TARGET= install install-dev

WRKSRC=		${WRKDIR}/attr-${VERSION}

post-install:
	cp ${WRKSRC}/libattr/.libs/libattr.a ${DESTDIR}${PREFIX}/lib
	cp ${WRKSRC}/libattr/.libs/libattr.so.1.1.0 ${DESTDIR}${PREFIX}/lib
	ln -sf libattr.so.1.1.0 ${DESTDIR}${PREFIX}/lib/libattr.so.1

.include "../../mk/bsd.pkg.mk"
