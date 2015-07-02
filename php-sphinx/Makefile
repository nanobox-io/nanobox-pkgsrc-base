# $NetBSD: Makefile,v 1.23 2013/03/17 10:46:45 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		sphinx
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		sysutils

MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		Alternative PHP Cache
LICENSE=		php


CONFLICTS=		php-sphinx-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
WRKSRC=			${WRKDIR}/sphinx-${PECL_VERSION}

PLIST_SRC+=		${.CURDIR}/PLIST.extras
PLIST_SUBST+=		PKGBASE=${PKGBASE:Q}

.include "../../base/php/extension_versions.mk"
.include "../../base/php/ext.mk"
.include "../../base/sphinxsearch-client/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
