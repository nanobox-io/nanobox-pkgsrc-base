# $NetBSD: Makefile,v 1.17 2012/10/02 21:25:40 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		pgsql
CATEGORIES+=		databases
COMMENT=		PHP extension for PostgreSQL databases

CONFLICTS=		php-pgsql-[0-9]*

CONFIGURE_ARGS+=	--with-${MODNAME}=shared,${PGSQL_PREFIX}

.include "../../base/php/ext.mk"
.include "../../mk/pgsql.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
