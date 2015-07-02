# $NetBSD: Makefile,v 1.17 2013/03/16 02:00:34 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
MODNAME=		pdo_mysql
PKGREVISION=		1
CATEGORIES+=		databases
COMMENT=		PHP extension for PHP Data Objects (MySQL)

USE_PHP_EXT_PATCHES=	yes

.include "../../mk/bsd.prefs.mk"

.include "../../base/php/ext.mk"
.if ${_PHP_VERSION} == "53"
CONFIGURE_ARGS+=	--with-${MODNAME}
CONFIGURE_ARGS+=	--with-${PKGMODNAME}=shared,${BUILDLINK_PREFIX.mysql-client}

.include "../../base/mysql/mysql.buildlink3.mk"
.else
CONFIGURE_ARGS+=	--with-${PKGMODNAME}=mysqlnd
.endif
.include "../../base/php-pdo/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"

