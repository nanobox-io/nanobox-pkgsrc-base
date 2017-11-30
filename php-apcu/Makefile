# $NetBSD: Makefile,v 1.23 2013/03/17 10:46:45 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		apcu
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		sysutils

MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		APC User Cache
LICENSE=		php

CONFLICTS=		php-apcu-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
WRKSRC=			${WRKDIR}/apcu-${PECL_VERSION}

.include "../../base/php/phpversion.mk"

.if ${PKG_PHP_MAJOR_VERS} == "7"
DISTINFO_FILE=		${.CURDIR}/distinfo-php70
PKGREVISION=		1
.endif

PLIST_SUBST+=		PKGBASE=${PKGBASE:Q}
PLIST_SUBST+=		PHP_VERSION=${_PHP_VERSION}

DOCDIR=			${PREFIX}/share/doc/${PKGBASE}

INSTALLATION_DIRS=	${DOCDIR}

PLIST_SRC+=		${.CURDIR}/../../base/php-apcu/PLIST.apcu

post-install:
	${INSTALL_DATA} ${WRKSRC}/INSTALL ${DESTDIR}${DOCDIR}

.include "../../base/php/extension_versions.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
