# $NetBSD: Makefile,v 1.13 2012/10/31 11:19:23 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		gettext
CATEGORIES+=		devel
COMMENT=		PHP extension for gettext support

CONFLICTS=		php-gettext-[0-9]*

CONFIGURE_ARGS+=	--with-gettext=shared,${BUILDLINK_DIR}

.include "../../base/php/ext.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
