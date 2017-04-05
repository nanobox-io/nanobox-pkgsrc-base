# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		rebar-${VERSION}
VERSION?=		2.6.4
# PKGREVISION?=		1
CATEGORIES=		pagoda
MASTER_SITES=		github.com/rebar/rebar

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		github.com/rebar/rebar
COMMENT=		rebar is an Erlang build tool that makes it easy to compile and test Erlang applications, port drivers and releases.
LICENSE=       		Apache 2.0

USE_TOOLS+=		gmake

BUILD_DEPENDS+=         erlang>=19.0.0:../../base/erlang19

WRKSRC=			${WRKDIR}/rebar

GIT_REPOSITORIES=	rebar
GIT_REPO.rebar=		git@github.com:rebar/rebar.git
GIT_TAG.rebar=		${VERSION}
#GIT_TAG=		master

SUBST_CLASSES+=		shebang
SUBST_FILES.shebang=	src/rebar_escripter.erl
SUBST_SED.shebang+=	-e 's,/usr/bin/env escript,${PREFIX}/bin/escript,'
SUBST_STAGE.shebang=	post-patch

do-build:
	cd ${WRKSRC}; ./bootstrap

do-install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp ${WRKSRC}/rebar ${DESTDIR}${PREFIX}/bin/rebar


.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"
