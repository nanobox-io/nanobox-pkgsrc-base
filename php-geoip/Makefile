# $NetBSD: Makefile,v 1.2 2012/10/23 17:18:58 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
#

MODNAME=		geoip
PECL_VERSION=		${PHP_EXTENSION_VERSION.geoip}
CATEGORIES=		net geography

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://pecl.php.net/package/geoip/
COMMENT=		PHP module to map IP address to geographic places
LICENSE=		php

CONFIGURE_ARGS+=	--with-${MODNAME}
CONFIGURE_ARGS+=	--with-${PKGMODNAME}=shared,${BUILDLINK_DIR}

.include "../../base/php/extension_versions.mk"
.include "../../base/php/ext.mk"
.include "../../net/GeoIP/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
