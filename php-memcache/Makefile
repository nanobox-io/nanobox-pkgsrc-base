# $NetBSD: Makefile,v 1.11 2012/10/31 11:19:23 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
#

MODNAME=		memcache
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		devel
COMMENT=		PHP extension for memcached

CONFLICTS=		php-memcache-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
CONFIGURE_ARGS+=  	--with-zlib-dir=${BUILDLINK_PREFIX.zlib}

WRKSRC=			${WRKDIR}/${MODNAME}-${PECL_VERSION}

.include "../../base/php/extension_versions.mk"

.if ${_PHP_VERSION} == "70" || ${_PHP_VERSION} == "71"
PATCHDIR=              ${.CURDIR}/../../base/php-memcache/patches7
.endif

.include "../../base/php/ext.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../base/php-session/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
