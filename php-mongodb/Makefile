# $NetBSD: Makefile,v 1.23 2013/03/17 10:46:45 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		mongodb
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		database

MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		MongoDB database driver
LICENSE=		php


CONFLICTS=		php-mongodb-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
CONFIGURE_ARGS+=	--with-openssl-dir=${BUILDLINK_PREFIX.openssl}
CONFIGURE_ARGS+=	--with-mongodb-sasl=${BUILDLINK_PREFIX.cyrus-sasl}
WRKSRC=			${WRKDIR}/mongodb-${PECL_VERSION}

# PLIST_SRC+=		${.CURDIR}/PLIST.extras
PLIST_SUBST+=		PKGBASE=${PKGBASE:Q}

.include "../../base/php/extension_versions.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../security/cyrus-sasl/buildlink3.mk"
# .include "../../base/php-json/buildlink3.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
