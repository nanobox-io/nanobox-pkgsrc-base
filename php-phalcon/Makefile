# $NetBSD: Makefile,v 1.1 2013/03/05 22:18:37 imil Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		phalcon
CATEGORIES+=		www
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
# PECL_LEGACY_VERSION_SCHEME=	yes

HOMEPAGE=		http://phalconphp.com/
COMMENT=		Phalcon is a web framework implemented as a C extension offering high performance and lower resource consumption
LICENSE=		php

INSTALLATION_DIRS=	${DOCDIR}

.include "../../base/php/extension_versions.mk"

GIT_REPOSITORIES=	phalcon
GIT_REPO.phalcon=	git://github.com/phalcon/cphalcon.git
.if ${_PHP_VERSION} == "53" || ${_PHP_VERSION} == "54"
GIT_TAG=		phalcon-v${PECL_VERSION}
.else
GIT_TAG=		v${PECL_VERSION}
.endif

WRKSRC=			${WRKDIR}/phalcon/ext

USE_LANGUAGES+=		c c++

USE_TOOLS+=		gmake

.include "../../base/php/ext.mk"
.include "../../base/php-pdo/buildlink3.mk"
.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"
