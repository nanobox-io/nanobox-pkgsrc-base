# $NetBSD: Makefile,v 1.16 2012/10/02 21:25:38 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		dba
CATEGORIES+=		databases
COMMENT=		PHP extension for DBM database access

CONFLICTS=		php-dba-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}=shared

CONFIGURE_ARGS+=	--with-cdb
CONFIGURE_ARGS+=	--without-dbm
CONFIGURE_ARGS+=	--with-inifile

.if exists(/usr/include/ndbm.h)
CONFIGURE_ARGS+=	--with-ndbm=/usr
.else
CONFIGURE_ARGS+=	--without-ndbm
.endif

.include "options.mk"

.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"