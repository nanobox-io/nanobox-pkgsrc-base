# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

.if !defined(GO_APP_MK)
GO_APP_MK=	#defined

BUILD_DEPENDS+=         go>=1.3.1:../../lang/go
BUILD_DEPENDS+=		mercurial>=3.3.2:../../devel/mercurial
BUILD_DEPENDS+=		bzr>=2.5.1:../../devel/bzr
.if exists(../../base/git/Makefile)
BUILD_DEPENDS+=         git>=1.6.4:../../base/git
.elif exists(../../devel/git/Makefile)
BUILD_DEPENDS+=         git-base>=1.6.4:../../devel/git-base
.else
BUILD_DEPENDS+=         scmgit-base>=1.6.4:../../devel/scmgit-base
.endif		

GOPATH=				${WRKDIR}/gocode
GOROOT=				${WRKDIR}/gocode

.if !defined(GO_DOMAIN) || !defined(GO_USER) || !defined(GO_PROJECT)
PKG_FAIL_REASON+=	'Please define GO_DOMAIN GO_USER and GO_PROJECT'
.endif

.PHONY: go-get-private go-get go-build go-install

go-copy:
	@${MKDIR} -p ${GOPATH}/src/${GO_DOMAIN}/${GO_USER}
	@${CP} -r ${WRKSRC} ${GOPATH}/src/${GO_DOMAIN}/${GO_USER}/${GO_PROJECT}

go-symlink:
	@${MKDIR} -p ${GOPATH}/src/${GO_DOMAIN}/${GO_USER}
	@${LN} -s ${WRKSRC} ${GOPATH}/src/${GO_DOMAIN}/${GO_USER}/${GO_PROJECT}

go-get: go-symlink
	@cd ${GOPATH}/src/${GO_DOMAIN}/${GO_USER}/${GO_PROJECT} && GOPATH=${GOPATH} ${PKGSRCDIR}/base/go/files/go-get.sh .

go-build: go-get
	@cd ${GOPATH}/src/${GO_DOMAIN}/${GO_USER}/${GO_PROJECT} && GOPATH=${GOPATH} go build

go-install:
	@cd ${GOPATH}/src/${GO_DOMAIN}/${GO_USER}/${GO_PROJECT} && GOPATH=${GOPATH} GOBIN=${DESTDIR}${PREFIX}/bin go install

.if !target(do-build)
do-build: go-build
.endif

.if !target(do-install)
do-install: go-install
.endif

.endif