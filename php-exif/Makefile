# $NetBSD: Makefile,v 1.12 2012/10/06 14:11:13 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		exif
CATEGORIES+=		graphics
COMMENT=		PHP extension to extract information from EXIF headers

CONFIGURE_ARGS+=	--with-${MODNAME}=shared
USE_PHP_EXT_PATCHES=	yes

.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
