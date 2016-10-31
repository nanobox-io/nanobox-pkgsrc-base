# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		rebar3-${VERSION}
VERSION?=		3.3.1
# PKGREVISION?=		1
CATEGORIES=		pagoda
MASTER_SITES=		github.com/erlang/rebar3

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		github.com/erlang/rebar3
COMMENT=		Rebar3 is an Erlang tool that makes it easy to create, develop, and release Erlang libraries, applications, and systems in a repeatable manner.
LICENSE=       		Apache 2.0

USE_TOOLS+=		gmake

BUILD_DEPENDS+=         erlang>=19.0.0:../../base/erlang19

WRKSRC=			${WRKDIR}/rebar3

GIT_REPOSITORIES=	rebar3
GIT_REPO.rebar3=	git@github.com:erlang/rebar3.git
GIT_TAG=		${VERSION}
#GIT_TAG=		master

SUBST_CLASSES+=		shebang
SUBST_FILES.shebang=	src/rebar_prv_escriptize.erl
SUBST_SED.shebang+=	-e 's,/usr/bin/env escript,${PREFIX}/bin/escript,'
SUBST_STAGE.shebang=	post-patch

do-build:
	cd ${WRKSRC}; ./bootstrap

do-install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp ${WRKSRC}/rebar3 ${DESTDIR}${PREFIX}/bin/rebar3


.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"
