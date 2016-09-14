# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		mongodb32-tools-${VERSION}
VERSION?=		3.2.9
# PKGREVISION?=		1
CATEGORIES=		pagoda
MASTER_SITES=		github.com/mongodb/mongo-tools

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		github.com/mongodb/mongo-tools
COMMENT=		Tools for managing mongodb
#LICENSE=       	# TODO: (see mk/license.mk)

WRKSRC=			${WRKDIR}/mongo-tools

USE_LANGUAGES=		# none

GIT_REPOSITORIES=	mongo-tools
GIT_REPO.mongo-tools=	git@github.com:mongodb/mongo-tools.git
GIT_TAG=		r${VERSION}

GO_DOMAIN=		github.com
GO_USER=		mongodb
GO_PROJECT=		mongo-tools

do-build:
	@cd ${WRKSRC}; ./build.sh

do-install:
	@mkdir -p ${DESTDIR}${PREFIX}
	@cp -r ${WRKSRC}/bin ${DESTDIR}${PREFIX}

.include "../../base/git/git-package.mk"
.include "../../base/go/go-app.mk"
.include "../../mk/bsd.pkg.mk"

