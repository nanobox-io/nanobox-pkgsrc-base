# $NetBSD: Makefile,v 1.2 2012/10/08 13:04:27 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		fileinfo
CATEGORIES+=		sysutils
COMMENT=		PHP extension for fileinfo conversion support

CONFLICTS=		php-fileinfo-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}

.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
