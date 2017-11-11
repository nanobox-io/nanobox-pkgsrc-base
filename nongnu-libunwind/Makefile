# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		libunwind-${VERSION}
VERSION=		1.2.1
PKGNAME=		nongnu-libunwind-${VERSION}
# PKGREVISION=		1
CATEGORIES=		lang
DISTFILES=		libunwind-${VERSION}.tar.gz

SITES.libunwind-${VERSION}.tar.gz=	http://download.savannah.nongnu.org/releases/libunwind/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://savannah.nongnu.org/projects/libunwind
COMMENT=		Libunwind defines a portable and efficient C programming interface (API) to determine the call-chain of a program.
LICENSE=		x11

USE_LANGUAGES+=		c c++

GNU_CONFIGURE=	yes

#USE_TOOLS+=	autoreconf autoconf automake

USE_LIBTOOL=	yes

.include "../../mk/bsd.pkg.mk"
