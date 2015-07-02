# $NetBSD: Makefile,v 1.13 2012/09/11 19:46:59 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		bz2
CATEGORIES=		archivers
COMMENT=		PHP extension for bzip2 compression

CONFLICTS=		php-bz2-[0-9]*

USE_PHP_EXT_PATCHES=	yes

CONFIGURE_ARGS+=	--with-${MODNAME}=shared,${BUILDLINK_PREFIX.bzip2}

.include "../../base/php/ext.mk"
.include "../../archivers/bzip2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"