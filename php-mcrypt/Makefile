# $NetBSD: Makefile,v 1.10 2012/10/23 18:16:50 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		mcrypt
CATEGORIES+=		security
COMMENT=		PHP extension for the mcrypt crypto algorithms library

CONFLICTS=		php-mcrypt-[0-9]*

CONFIGURE_ARGS+=	--with-${MODNAME}=shared,${BUILDLINK_PREFIX.libmcrypt}

.include "../../base/php/extension_versions.mk"
.if ${_PHP_VERSION} == "72"
DISTINFO_FILE=		${.CURDIR}/distinfo-php72
PECL_VERSION=           ${PHP_EXTENSION_VERSION.${MODNAME}}
.endif


.include "../../base/php/ext.mk"


.include "../../security/libmcrypt/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
