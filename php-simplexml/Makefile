# $NetBSD: Makefile,v 1.2 2012/10/08 13:04:27 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		simplexml
CATEGORIES+=		textproc
COMMENT=		PHP extension for simplexml

CONFLICTS=		php-simplexml-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
CONFIGURE_ARGS+=	--with-libxml-dir=${BUILDLINK_PREFIX.libxml2}

.include "../../textproc/libxml2/buildlink3.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
