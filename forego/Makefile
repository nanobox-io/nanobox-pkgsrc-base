# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		forego-${VERSION}
VERSION?=		0.16.1
# PKGREVISION?=		1
CATEGORIES=		pagoda
MASTER_SITES=		github.com/ddollar/forego

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		github.com/ddollar/forego
COMMENT=		Foreman in Go
LICENSE=       		APL2

WRKSRC=			${WRKDIR}/forego

USE_LANGUAGES=		# none

GIT_REPOSITORIES=	forego
GIT_REPO.forego=	git@github.com:ddollar/forego.git
GIT_TAG.forego=		v${VERSION}

GO_DOMAIN=		github.com
GO_USER=		ddollar
GO_PROJECT=		forego

.include "../../base/git/git-package.mk"
.include "../../base/go/go-app.mk"
.include "../../mk/bsd.pkg.mk"

