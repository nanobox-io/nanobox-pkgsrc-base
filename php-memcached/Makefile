# $NetBSD: Makefile,v 1.23 2013/03/17 10:46:45 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		memcached
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		sysutils

MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		PHP extension for interfacing with memcached via libmemcached library
LICENSE=		php

USE_TOOLS+=		pkg-config

CONFLICTS=		php-memcached-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
CONFIGURE_ARGS+=	--enable-memcached-igbinary
CONFIGURE_ARGS+=	--enable-memcached-json 
CONFIGURE_ARGS+=	--with-zlib-dir=${BUILDLINK_PREFIX.zlib}
CONFIGURE_ARGS+=	--with-libmemcached-dir=${BUILDLINK_PREFIX.libmemcached}

WRKSRC=			${WRKDIR}/memcached-${PECL_VERSION}

PLIST_SRC+=		${.CURDIR}/PLIST.extras
PLIST_SUBST+=		PKGBASE=${PKGBASE:Q}

.include "../../base/php/extension_versions.mk"

.if ${PKG_PHP_MAJOR_VERS} == "7"
DISTINFO_FILE=          ${.CURDIR}/distinfo-php70
.endif

.include "../../base/php-json/buildlink3.mk"
.include "../../base/php-session/buildlink3.mk"
.include "../../base/php-igbinary/buildlink3.mk"
.include "../../devel/libmemcached/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
