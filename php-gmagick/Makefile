# $NetBSD: Makefile,v 1.23 2013/03/17 10:46:45 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		gmagick
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		graphics
#PKGREVISION=		1

MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		Provides a wrapper to the GraphicsMagick library.
LICENSE=		php

.include "../../base/php/phpversion.mk"
.if ${PKG_PHP_MAJOR_VERS} == "7"
PKGREVISION=		1
DISTINFO_FILE=		${.CURDIR}/distinfo-php70
PECL_DISTNAME=		gmagick-${PECL_VERSION}RC1
WRKSRC=                 ${WRKDIR}/gmagick-${PECL_VERSION}RC1
.else
PKGREVISION=		3
PECL_DISTNAME=          gmagick-${PECL_VERSION}RC3
WRKSRC=                 ${WRKDIR}/gmagick-${PECL_VERSION}RC3
.endif

CONFLICTS=		php-gmagick-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
CONFIGURE_ARGS+=	--with-gmagick=${BUILDLINK_PREFIX.GraphicsMagick}

CFLAGS+=		-Wno-deprecated-declarations

PLIST_SRC+=		${.CURDIR}/PLIST.extras
PLIST_SUBST+=		PKGBASE=${PKGBASE:Q}

INSTALLATION_DIRS+=	include/php/ext/gmagick

GMAGICK_INCLUDES=	php_gmagick.h php_gmagick_helpers.h php_gmagick_macros.h	

post-install:
.for inc in ${GMAGICK_INCLUDES}
	${INSTALL_DATA} ${WRKSRC}/${inc} ${DESTDIR}${PREFIX}/include/php/ext/gmagick/${inc}
.endfor

#DEPENDS+=	ghostscript>=9:../../print/ghostscript

.include "../../base/php/extension_versions.mk"
.include "../../graphics/GraphicsMagick/buildlink3.mk"
#.include "../../mk/jpeg.buildlink3.mk"
#.include "../../archivers/bzip2/buildlink3.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
