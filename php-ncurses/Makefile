# $NetBSD: Makefile,v 1.23 2013/03/17 10:46:45 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		ncurses
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		devel

MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		Terminal screen handling and optimization package
LICENSE=		php


CONFLICTS=		php-ncurses-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
CONFIGURE_ARGS+=	--with-ncurses=${BUILDLINK_PREFIX.ncurses}
WRKSRC=			${WRKDIR}/ncurses-${PECL_VERSION}

PLIST_SRC+=		${.CURDIR}/PLIST.extras
PLIST_SUBST+=		PKGBASE=${PKGBASE:Q}

.include "../../base/php/extension_versions.mk"
.include "../../devel/ncurses/buildlink3.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
