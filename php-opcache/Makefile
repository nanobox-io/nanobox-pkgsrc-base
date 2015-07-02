# $NetBSD: Makefile,v 1.1 2013/03/05 22:18:37 imil Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		opcache
PKGMODNAME=		opcache
CATEGORIES+=		www
# PECL_LEGACY_VERSION_SCHEME=	yes
.include "../../base/php/phpversion.mk"

.if ${_PHP_VERSION} == "53" || ${_PHP_VERSION} == "54"

PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}

HOMEPAGE=		https://github.com/zend-dev/ZendOptimizerPlus
MAINTAINER=		imil@NetBSD.org
COMMENT=		Zend opcode cache and optimizer for PHP
LICENSE=		php

PLIST_SRC+=		${.CURDIR}/PLIST.extras
PLIST_SUBST+=		PKGBASE=${PKGBASE:Q}

DOCDIR=			${PREFIX}/share/doc/${PKGBASE}

INSTALLATION_DIRS=	${DOCDIR}

GIT_REPOSITORIES=	opcache
GIT_REPO.opcache=	git@github.com:zendtech/ZendOptimizerPlus.git
GIT_TAG=		v${PECL_VERSION}

WRKSRC=			${WRKDIR}/opcache

.include "../../base/php/ext.mk"
# this is not an usual extension, override MESSAGE.module
MESSAGE_SRC=           ${.CURDIR}/MESSAGE

post-install:
	${INSTALL_DATA} ${WRKSRC}/README ${DESTDIR}${DOCDIR}

.include "../../base/git/git-package.mk"
.else
USE_PHP_EXT_PATCHES=	yes
.include "../../base/php/ext.mk"
.endif

.include "../../base/php/extension_versions.mk"

.include "../../mk/bsd.pkg.mk"
