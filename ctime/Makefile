# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		ctime-${VERSION}
VERSION?=		0.1.0
# PKGREVISION?=		1
CATEGORIES=		nanobox
MASTER_SITES=		github.com/glinton/ctime

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		github.com/glinton/ctime
COMMENT=		A touch-like utility to trigger filesystem events
LICENSE=       		MIT

WRKSRC=			${WRKDIR}/ctime

USE_LANGUAGES=		# none

GIT_REPOSITORIES=	ctime
GIT_REPO.ctime=		git@github.com:glinton/ctime.git
GIT_TAG.ctime=		v${VERSION}

GO_DOMAIN=		github.com
GO_USER=		glinton
GO_PROJECT=		ctime

.include "../../base/git/git-package.mk"
.include "../../base/go/go-app.mk"
.include "../../mk/bsd.pkg.mk"

