# $NetBSD: Makefile,v 1.2 2012/10/23 17:18:58 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
#

MODNAME=		gnupg
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES=		net

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://pecl.php.net/package/${MODNAME}/
COMMENT=		wrapper around the gpgme library
LICENSE=		php

CONFIGURE_ARGS+=	--with-${MODNAME}
CONFIGURE_ARGS+=	--with-${PKGMODNAME}=shared,${BUILDLINK_DIR}

LIBS.SunOS+=		-lnsl -lsocket

SUBST_CLASSES+=		paths
SUBST_STAGE.paths=	pre-configure
SUBST_FILES.paths=	config.m4 configure
SUBST_SED.paths=	-e "s|@PREFIX@|${PREFIX}|g"
SUBST_MESSAGE.paths=	Fixing paths.

.include "../../base/php/extension_versions.mk"
.include "../../base/php/ext.mk"
.include "../../security/gpgme/buildlink3.mk"
.include "../../security/gnupg2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
