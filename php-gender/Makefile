# $NetBSD: Makefile,v 1.2 2012/10/23 17:18:58 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
#

MODNAME=		gender
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES=		net

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://pecl.php.net/package/${MODNAME}/
COMMENT=		Gender Extension
LICENSE=		php

CONFIGURE_ARGS+=	--with-${MODNAME}
CONFIGURE_ARGS+=	--with-${PKGMODNAME}=shared,${BUILDLINK_DIR}

.include "../../base/php/extension_versions.mk"

.if ${_PHP_VERSION} == "70"
PKGREVISION=		1
.endif

.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
