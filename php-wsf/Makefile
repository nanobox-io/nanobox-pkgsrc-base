# $NetBSD: Makefile,v 1.1 2013/03/05 22:18:37 imil Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		wsf
CATEGORIES+=		www
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
PKGREVISION=		3
PKGBASE?=		${PHP_PKG_PREFIX}-${MODNAME}
VERSION?=		${PECL_VERSION}
PKGNAME?=		${PKGBASE}-${VERSION}
# PECL_LEGACY_VERSION_SCHEME=	yes

HOMEPAGE=		https://github.com/notxarb/wsf-php
COMMENT=		WSO2 Web Services Framework for PHP (WSO2 WSF/PHP)
LICENSE=		php

GIT_REPOSITORIES=	wsf
GIT_REPO.wsf=		git://github.com/notxarb/wsf-php.git
GIT_TAG=		master

GNU_CONFIGURE=		YES
CONFIGURE_ARGS+=	--with-libxml-dir=${BUILDLINK_PREFIX.libxml2}
BUILDLINK_INCDIRS.libxml2?= include/libxml2

WRKSRC=			${WRKDIR}/wsf

USE_LANGUAGES+=		c c++

USE_TOOLS+=		gmake
INSTALL_ENV+=		INSTALL_ROOT=${DESTDIR}
INSTALL_ENV+=		DESTDIR=${DESTDIR}

# SUBST_CLASSES+=		paths
# SUBST_STAGE.paths=	pre-configure
# SUBST_FILES.paths=	config.m4 configure
# SUBST_SED.paths=	-e "s|@PREFIX@|${PREFIX}|g"
# SUBST_MESSAGE.paths=	Fixing paths.

.include "../../base/php/extension_versions.mk"
# .include "../../base/php/ext.mk"
.include "${PHPPKGSRCDIR}/buildlink3.mk"

.include "../../base/git/git-package.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
