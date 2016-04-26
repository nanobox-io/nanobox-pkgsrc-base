# $NetBSD: Makefile,v 1.23 2013/03/17 10:46:45 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		raphf
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		devel

MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		raphf extension
LICENSE=		php


CONFLICTS=		php-raphf-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
WRKSRC=			${WRKDIR}/raphf-${PECL_VERSION}

PLIST_SRC+=		${.CURDIR}/PLIST.extras
PLIST_SUBST+=		PKGBASE=${PKGBASE:Q}

RAPHF_INCLUDES=		php_raphf.h
RAPHF_SRC_INCLUDES=	php_raphf_api.h

INSTALLATION_DIRS+=	include/php/ext/raphf

post-install:
.for inc in ${RAPHF_INCLUDES}
	${INSTALL_DATA} ${WRKSRC}/${inc} ${DESTDIR}${PREFIX}/include/php/ext/raphf/${inc}
.endfor

.for inc in ${RAPHF_SRC_INCLUDES}
	${INSTALL_DATA} ${WRKSRC}/src/${inc} ${DESTDIR}${PREFIX}/include/php/ext/raphf/${inc}
.endfor

.include "../../base/php/extension_versions.mk"

.if ${_PHP_VERSION} == "70"
DISTINFO_FILE=		${.CURDIR}/distinfo-php70
.endif

.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"