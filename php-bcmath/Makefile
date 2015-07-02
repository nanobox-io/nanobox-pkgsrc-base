# $NetBSD: Makefile,v 1.9 2012/09/11 23:04:30 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		bcmath
CATEGORIES+=		math
COMMENT=		PHP extension for bc-style arbitrary precision math

CONFLICTS=		php-bcmath-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}

USE_PHP_EXT_PATCHES=	yes

.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"