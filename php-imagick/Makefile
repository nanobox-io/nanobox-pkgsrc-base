# $NetBSD: Makefile,v 1.23 2013/03/17 10:46:45 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		imagick
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		sysutils
PKGREVISION=		2

MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		Provides a wrapper to the ImageMagick library.
LICENSE=		php

.include "../../base/php/phpversion.mk"
.if ${_PHP_VERSION} == "70" || ${_PHP_VERSION} == "71" || ${_PHP_VERSION} == "72"
DISTINFO_FILE=		${.CURDIR}/distinfo-php70
.endif

CONFLICTS=		php-imagick-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
CONFIGURE_ARGS+=	--with-imagick=${BUILDLINK_PREFIX.ImageMagick6}

CFLAGS+=		-Wno-deprecated-declarations

WRKSRC=			${WRKDIR}/imagick-${PECL_VERSION}

PLIST_SRC+=		${.CURDIR}/PLIST.extras
PLIST_SUBST+=		PKGBASE=${PKGBASE:Q}

INSTALLATION_DIRS+=	include/php/ext/imagick

IMAGICK_INCLUDES=	php_imagick_defs.h php_imagick_file.h php_imagick_helpers.h php_imagick_macros.h php_imagick_shared.h php_imagick.h

post-install:
.for inc in ${IMAGICK_INCLUDES}
	${INSTALL_DATA} ${WRKSRC}/${inc} ${DESTDIR}${PREFIX}/include/php/ext/imagick/${inc}
.endfor

DEPENDS+=	ghostscript>=9:../../print/ghostscript

.include "../../base/php/extension_versions.mk"
.include "../../graphics/ImageMagick6/buildlink3.mk"
.include "../../mk/jpeg.buildlink3.mk"
.include "../../archivers/bzip2/buildlink3.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
