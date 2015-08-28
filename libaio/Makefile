# $NetBSD: Makefile,v 1.1 2013/03/05 22:18:37 imil Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

VERSION=		0.3.110-1
DISTNAME=		libaio-${VERSION}
# PKGREVISION=		1
PKGNAME=		libaio-${VERSION:S/-/./}
CATEGORIES=		devel
MASTER_SITES=		https://git.fedorahosted.org/cgit/libaio.git

HOMEPAGE=		https://git.fedorahosted.org/cgit/libaio.git
COMMENT=		WSO2 Web Services Framework for PHP (WSO2 WSF/PHP)
LICENSE=		php

BUILD_DEPENDS+=         coreutils>=8.22:../../sysutils/coreutils

GIT_REPOSITORIES=	libaio
GIT_REPO.libaio=	https://git.fedorahosted.org/git/libaio.git
GIT_TAG=		libaio-0.3.110-1

USE_CONFIGURE=		No

WRKSRC=			${WRKDIR}/libaio

USE_LANGUAGES+=		c

USE_TOOLS+=		gmake

TOOLS_PLATFORM.install=	${PREFIX}/gnu/bin/install

SUBST_CLASSES+=		makefile
SUBST_STAGE.makefile=	post-patch
SUBST_FILES.makefile=	Makefile src/Makefile
SUBST_SED.makefile=	-e "s|@PREFIX@|${PREFIX}|g"
SUBST_MESSAGE.makefile=	Fixing prefix in Makefile

.include "../../base/git/git-package.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
