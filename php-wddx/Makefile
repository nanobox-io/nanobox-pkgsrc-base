# $NetBSD: Makefile,v 1.18 2012/10/25 06:56:46 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		wddx
CATEGORIES+=		textproc
COMMENT=		PHP extension for WDDX support

CONFLICTS=		php-wddx-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}=shared,${BUILDLINK_DIR}
CONFIGURE_ARGS+=	--with-libxml-dir=${BUILDLINK_DIR}

CPPFLAGS+=  		-I${WRKDIR}/${DISTNAME}

USE_PHP_EXT_PATCHES=	# defined

# appease some PHP build assumpsions
CFLAGS+=		-I${BUILDLINK_DIR}/include/libxml2 \
			-I${BUILDLINK_DIR}/include/php/ext/date/lib

.include "../../base/php/phpversion.mk"
.include "../../base/php-session/buildlink3.mk"
.include "../../base/php-xml/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
