# $NetBSD: Makefile,v 1.1 2013/03/05 22:18:37 imil Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		elixir-${VERSION}
VERSION=		1.6.2
PKGNAME=		${ERLANG_PKGPREFIX}-elixir-${VERSION}
PKGREVISION=		1
CATEGORIES=		base
MASTER_SITES=		http://elixir-lang.org/

HOMEPAGE=		http://elixir-lang.org/
COMMENT=		Elixir is a dynamic, functional language designed for building scalable and maintainable applications.
LICENSE=		Apache

GIT_REPOSITORIES=	elixir
GIT_REPO.elixir=	git@github.com:elixir-lang/elixir.git
GIT_TAG.elixir=		v${VERSION}

BUILD_TARGET=		compile

WRKSRC=			${WRKDIR}/elixir

USE_LANGUAGES+=		c c++

USE_TOOLS+=		gmake gsed

INSTALL_ENV+=		DESTDIR=${DESTDIR}

SUBST_CLASSES+=		paths
SUBST_STAGE.paths=	post-patch
SUBST_FILES.paths=	Makefile
SUBST_SED.paths=	-e "s|@PREFIX@|${PREFIX}|g"
SUBST_MESSAGE.paths=	Fixing paths.

.include "../../base/git/git-package.mk"
.include "../../base/erlang/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"

MAKE_ENV +=	LC_CTYPE="en_US.UTF-8"
MAKE_ENV +=	LC_LANG="en_US.UTF-8"
MAKE_ENV +=	LC_ALL=""
