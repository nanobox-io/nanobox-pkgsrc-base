# $NetBSD: Makefile,v 1.2 2014/05/29 23:35:35 wiz Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

VERSION=	2.2.52
DISTNAME=	acl-${VERSION}.src
# PKGREVISION=	1
PKGNAME=	libacl-${VERSION}
CATEGORIES=	devel
MASTER_SITES=	http://download.savannah.gnu.org/releases/acl/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://savannah.nongnu.org/projects/acl
COMMENT=	Commands for Manipulating POSIX Access Control Lists
LICENSE=	GPL2

USE_TOOLS+=	gmake

GNU_CONFIGURE=	yes
USE_LANGUAGES=	c c++

OVERRIDE_DIRDEPTH.install-sh= -1
OVERRIDE_DIRDEPTH.libtool= -1

BUILD_TARGET=
INSTALL_TARGET= install install-dev

WRKSRC=		${WRKDIR}/acl-${VERSION}

post-install:
	cp ${WRKSRC}/libacl/.libs/libacl.a ${DESTDIR}${PREFIX}/lib
	cp ${WRKSRC}/libacl/.libs/libacl.so.1.1.0 ${DESTDIR}${PREFIX}/lib
	ln -sf libacl.so.1.1.0 ${DESTDIR}${PREFIX}/lib/libacl.so.1

.include "../../base/libattr/buildlink3.mk"
.include "../../devel/gettext-tools/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
