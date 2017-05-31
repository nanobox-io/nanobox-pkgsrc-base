# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
#

MODNAME=		magickwand
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
PECL_DISTNAME=		MagickWandForPHP-1.0.9-2
PKGNAME=		${PHP_PKG_PREFIX}-${MODNAME}-${PECL_VERSION}
PKGREVISION=		1
CATEGORIES=		www
MASTER_SITES=		http://www.magickwand.org/download/php/
EXTRACT_SUFX=		.tar.gz # required, because ../../base/php/ext.mk
				# overrides it with .tgz

# Original Maintainer (since dec 2010)
#MAINTAINER=		mbowie@buzmo.com
# Maintainer from dec 2010 on
MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://www.magickwand.org/
COMMENT=		This module enables PHP access to the ImageMagick MagickWand API.

WRKSRC=			${WRKDIR}/MagickWandForPHP-1.0.9

PLIST_SRC+=		PLIST

CONFIGURE_ARGS+=	--enable-${MODNAME}

.include "../../mk/bsd.prefs.mk"

.include "../../base/php/extension_versions.mk"
.include "../../base/php/ext.mk"
.include "../../graphics/ImageMagick6/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
