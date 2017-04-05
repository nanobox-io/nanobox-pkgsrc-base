# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

PKGNAME=		${PHP_PKG_PREFIX}-blackfire-${PHP_EXTENSION_VERSION.${MODNAME}}
DISTFILES=		blackfire-php-linux_amd64-php-${PKG_PHP_VERSION}.so
PKGBASE=		${PHP_PKG_PREFIX}-blackfire
MODNAME=		blackfire
VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
MASTER_SITES=		https://packages.blackfire.io/binaries/blackfire-php/${PHP_EXTENSION_VERSION.${MODNAME}}/
CATEGORIES=		www

DISTINFO_FILE=		${.CURDIR}/distinfo-${PHP_PKG_PREFIX}

NO_BUILD=		yes
NO_CONFIGURE=		yes

MODULESDIR=		${WRKDIR}

DEPENDS+=		blackfire>=1.9.2:../../base/blackfire

PLIST_SUBST+=           PHP_EXTENSION_DIR=${PHP_EXTENSION_DIR}
PLIST_SRC+=             ${.CURDIR}/../../base/php/PLIST.module
PLIST_SUBST+=           MODNAME=${MODNAME}


post-patch:
	cp -r ${WRKDIR}/blackfire-php-linux_amd64-php-${PKG_PHP_VERSION}.so ${WRKDIR}/${MODNAME}.so

do-install:
	mkdir -p ${DESTDIR}${PREFIX}/${PHP_EXTENSION_DIR}
	cp -r ${WRKDIR}/${MODNAME}.so ${DESTDIR}${PREFIX}/${PHP_EXTENSION_DIR}/${MODNAME}.so

.include "../../mk/bsd.prefs.mk"
.include "../../base/php/phpversion.mk"
.include "../../base/php/extension_versions.mk"
.include "../../base/php-session/buildlink3.mk"
#.include "../../base/php/ext.mk"
.include "${PHPPKGSRCDIR}/Makefile.common"
.include "../../mk/bsd.pkg.mk"
