# $NetBSD: Makefile,v 1.9 2013/03/16 02:00:33 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		mysqli
PKGREVISION=		1
CATEGORIES+=		databases
COMMENT=		PHP5 extension for MySQL 4.1 and later databases

MAINTAINER=		pkgsrc-users@NetBSD.org

CONFLICTS=		php-mysqli-[0-9]*

.include "../../base/php/ext.mk"
.if ${_PHP_VERSION} == "53"
EVAL_PREFIX+=		MYSQLDIR=mysql-client
CONFIGURE_ARGS+=	--with-${MODNAME}=${PREFIX}/bin/mysql_config
.include "../../base/mysql/mysql.buildlink3.mk"
.else
CONFIGURE_ARGS+=	--with-${MODNAME}=mysqlnd
.endif
.include "../../mk/bsd.pkg.mk"
