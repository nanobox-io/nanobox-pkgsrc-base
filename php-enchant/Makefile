# $NetBSD: Makefile,v 1.11 2012/10/25 06:56:45 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=			enchant
CATEGORIES+=			textproc
COMMENT=			PHP extension for ENCHANT (spelling) support

CONFIGURE_ARGS+=		--with-enchant=shared,${BUILDLINK_PREFIX.enchant}

BUILDLINK_API_DEPENDS.enchant+=	enchant>=1.2.4

.include "../../base/php/ext.mk"
.include "../../textproc/enchant/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
