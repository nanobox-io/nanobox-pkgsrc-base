# $NetBSD: Makefile,v 1.2 2012/10/08 13:04:27 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		phar
CATEGORIES+=		archivers
COMMENT=		PHP extension for phar conversion support

CONFLICTS=		php-phar-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}

SUBST_CLASSES+=		paths
SUBST_STAGE.paths=	pre-configure
SUBST_FILES.paths=	ext/phar/phar/phar.php
SUBST_SED.paths=	-e "s|@PREFIX@|${PREFIX}|g"
SUBST_MESSAGE.paths=	Fixing paths.

.include "../../base/php-hash/buildlink3.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
