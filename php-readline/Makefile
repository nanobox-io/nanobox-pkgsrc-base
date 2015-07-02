# $NetBSD: Makefile,v 1.2 2012/10/08 13:04:27 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		readline
CATEGORIES+=		textproc
COMMENT=		PHP extension for readline support

CONFLICTS=		php-readline-[0-9]*

USE_PHP_EXT_PATCHES=	yes

.include "../../mk/bsd.prefs.mk"
.include "../../base/php/ext.mk"

CONFIGURE_ARGS+=	--enable-${MODNAME}
CONFIGURE_ARGS+=	--with-readline=${BUILDLINK_PREFIX.readline}

EDITLINE_SKIP_FNAME_TRANSFORM=	yes

.include "../../devel/editline/buildlink3.mk"
.include "../../devel/readline/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
