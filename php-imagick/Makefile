# $NetBSD: Makefile,v 1.23 2013/03/17 10:46:45 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		imagick
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		sysutils

MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		Provides a wrapper to the ImageMagick library.
LICENSE=		php


CONFLICTS=		php-imagick-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
CONFIGURE_ARGS+=	--with-imagick=${BUILDLINK_PREFIX.ImageMagick}

WRKSRC=			${WRKDIR}/imagick-${PECL_VERSION}

PLIST_SRC+=		${.CURDIR}/PLIST.extras
PLIST_SUBST+=		PKGBASE=${PKGBASE:Q}

DOCDIR=			${PREFIX}/share/doc/${PKGBASE}

INSTALLATION_DIRS=	${DOCDIR}
INSTALLATION_DIRS+=	include/php/ext/imagick

IMAGICK_INCLUDES=	php_imagick_defs.h php_imagick_file.h php_imagick_helpers.h php_imagick_macros.h php_imagick_shared.h php_imagick.h

post-install:
.for inc in ${IMAGICK_INCLUDES}
	${INSTALL_DATA} ${WRKSRC}/${inc} ${DESTDIR}${PREFIX}/include/php/ext/imagick/${inc}
.endfor
	${INSTALL_DATA} ${WRKSRC}/INSTALL ${DESTDIR}${DOCDIR}

DEPENDS+=	ghostscript>=9:../../print/ghostscript

.include "../../base/php/extension_versions.mk"
.include "../../graphics/ImageMagick/buildlink3.mk"
.include "../../graphics/libjpeg-turbo/buildlink3.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"