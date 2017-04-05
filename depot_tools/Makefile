# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		depot_tools-${VERSION}
VERSION?=		0.0.1
# PKGREVISION?=		1
CATEGORIES=		pagoda
MASTER_SITES=		http://dev.chromium.org/developers/how-tos/install-depot-tools

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://dev.chromium.org/developers/how-tos/install-depot-tools
COMMENT=		Google depot tools
LICENSE=       		The Chromium Authors

WRKSRC=			${WRKDIR}/depot_tools

NO_BUILD=	yes

GIT_REPOSITORIES=	depot_tools
GIT_REPO.depot_tools=	https://chromium.googlesource.com/chromium/tools/depot_tools.git
# GIT_TAG=		${VERSION}
GIT_BRANCH.depot_tools=	master

pre-install:
	rm -rf ${WRKSRC}/.git

do-install:
	mkdir ${DESTDIR}${PREFIX}
	cp -r ${WRKSRC} ${DESTDIR}${PREFIX}

.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"
