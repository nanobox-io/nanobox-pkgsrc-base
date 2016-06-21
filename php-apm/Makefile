# $NetBSD: Makefile,v 1.2 2012/10/23 17:18:58 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
#

MODNAME=		apm
PKGREVISION=		1
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
PECL_DISTNAME= 		APM-${PECL_VERSION}
CATEGORIES=		devel

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://pecl.php.net/package/${MODNAME}/
COMMENT=		PHP module for Alternative PHP Monitor
LICENSE=		php

.include "../../base/php/phpversion.mk"

CONFIGURE_ARGS+=	--with-${MODNAME}
CONFIGURE_ARGS+=	--with-${PKGMODNAME}=shared,${BUILDLINK_DIR}
CONFIGURE_ARGS+=	--with-sqlite3=${BUILDLINK_PREFIX.sqlite3}
CONFIGURE_ARGS+=	--with-mysql=${BUILDLINK_PREFIX.mysql-client}
CONFIGURE_ARGS+=	--with-zlib-dir=${BUILDLINK_PREFIX.zlib}

.if ${_PHP_VERSION} == "53"
DISTINFO_FILE=		${.CURDIR}/distinfo-php53
.endif

.include "../../base/php/extension_versions.mk"
.include "../../base/php/ext.mk"
.include "../../base/php-json/buildlink3.mk"
.include "../../databases/sqlite3/buildlink3.mk"
.include "../../databases/sqlite/buildlink3.mk"
.include "../../base/mysql/mysql.buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
