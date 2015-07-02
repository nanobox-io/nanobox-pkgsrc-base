# $NetBSD: Makefile,v 1.19 2013/03/16 02:00:33 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		mysql
PKGREVISION=		1
CATEGORIES+=		databases
COMMENT=		PHP extension for MySQL databases

MAINTAINER=		pkgsrc-users@NetBSD.org

CONFLICTS=		php-mysql-[0-9]*

USE_PHP_EXT_PATCHES=	yes
.include "../../base/php/ext.mk"

.if ${_PHP_VERSION} == "53"
EVAL_PREFIX+=		MYSQLDIR=mysql-client
CONFIGURE_ARGS+=	--with-${MODNAME}=shared,${MYSQLDIR}
CONFIGURE_ENV+=		CPP=${CPP:Q}
LDFLAGS+=		${COMPILER_RPATH_FLAG}${LOCALBASE}/lib/mysql
.include "../../base/mysql/mysql.buildlink3.mk"
.else
CONFIGURE_ARGS+=	--with-${MODNAME}=mysqlnd
.endif
.include "../../mk/bsd.pkg.mk"
