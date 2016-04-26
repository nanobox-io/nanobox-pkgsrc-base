# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
#  # vim: ts=8 sw=8 ft=make noet

MODNAME=		timezonedb
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		sysutils

MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		Timezone Database to be used with PHP's date and time functions
LICENSE=		php


CONFLICTS=		php-timezonedb-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
WRKSRC=			${WRKDIR}/timezonedb-${PECL_VERSION}

PLIST_SRC+=		${.CURDIR}/PLIST.extras
PLIST_SUBST+=		PKGBASE=${PKGBASE:Q}

.include "../../base/php/extension_versions.mk"

.if ${_PHP_VERSION} == "70"
PKGREVISION=		1
.endif

.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
