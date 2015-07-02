# $NetBSD: Makefile,v 1.1 2013/03/05 22:18:37 imil Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		wsf
CATEGORIES+=		www
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
PKGREVISION=		3
# PECL_LEGACY_VERSION_SCHEME=	yes

HOMEPAGE=		https://github.com/notxarb/wsf-php
COMMENT=		WSO2 Web Services Framework for PHP (WSO2 WSF/PHP)
LICENSE=		php

GIT_REPOSITORIES=	wsf
GIT_REPO.wsf=		git://github.com/notxarb/wsf-php.git
GIT_TAG=		master

WRKSRC=			${WRKDIR}/wsf

USE_LANGUAGES+=		c c++

USE_TOOLS+=		gmake

.include "../../base/php/extension_versions.mk"
.include "../../base/php/ext.mk"
.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"
