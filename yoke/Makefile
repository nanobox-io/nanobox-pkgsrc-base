# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		yoke-${VERSION}
VERSION?=		0.0.4
# PKGREVISION?=		1
CATEGORIES=		pagoda
MASTER_SITES=		github.com/pagodabox/yoke

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		github.com/pagodabox/yoke
COMMENT=		Yoke is a postgres redundancy/auto-failover solution
LICENSE=       		MIT

WRKSRC=			${WRKDIR}/yoke

USE_LANGUAGES=		# none

GIT_REPOSITORIES=	yoke
GIT_REPO.yoke=		git@github.com:pagodabox/yoke.git
GIT_TAG=		${VERSION}

GO_DOMAIN=		github.com
GO_USER=		pagodabox
GO_PROJECT=		yoke

.PHONY: build-yokeadm install-yokeadm

post-build: build-yokeadm

post-install: install-yokeadm

build-yokeadm:
	@cd ${GOPATH}/src/${GO_DOMAIN}/${GO_USER}/${GO_PROJECT}/yokeadm && GOPATH=${GOPATH} go build

install-yokeadm:
	@cd ${GOPATH}/src/${GO_DOMAIN}/${GO_USER}/${GO_PROJECT}/yokeadm && GOPATH=${GOPATH} GOBIN=${DESTDIR}${PREFIX}/bin go install

.include "../../base/git/git-package.mk"
.include "../../base/go/go-app.mk"
.include "../../mk/bsd.pkg.mk"

