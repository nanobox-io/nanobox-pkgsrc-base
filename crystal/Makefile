# $NetBSD: Makefile,v 1.1 2013/03/05 22:18:37 imil Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		crystal-${VERSION}
PKGNAME=		crystal-${VERSION}
PKGREVISION=		1
CATEGORIES=		lang
MASTER_SITES=		https://crystal-lang.org/

HOMEPAGE=		https://crystal-lang.org/
COMMENT=		Crystal language
LICENSE=		apache-2.0

USE_TOOLS+=		gmake
USE_LANGUAGES+=		c c++

GIT_REPOSITORIES=	crystal shards
GIT_REPO.crystal=	https://github.com/crystal-lang/crystal.git
GIT_TAG.crystal=	${VERSION}

GIT_REPO.shards=	git@github.com:crystal-lang/shards.git
GIT_TAG.shards=		v0.7.2

WRKSRC=			${WRKDIR}/crystal

BUILD_DEPENDS=		crystal-omnibus>=${VERSION}:../../base/crystal-omnibus

PREPEND_PATH+=		${PREFIX}/crystal-omnibus/bin

MAKE_FLAGS+=		release=1
MAKE_FLAGS+=		progress=true
MAKE_FLAGS+=		threads=${MAKE_JOBS}
MAKE_FLAGS+=		stats=true
MAKE_FLAGS+=		verbose=true

.include "../../lang/llvm/buildlink3.mk"
.include "../../devel/libevent/buildlink3.mk"
.include "../../devel/editline/buildlink3.mk"
.include "../../devel/gmp/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../textproc/libyaml/buildlink3.mk"
.include "../../devel/readline/buildlink3.mk"
.include "../../devel/pcre/buildlink3.mk"
.include "../../base/crystal/crystalversion.mk"
.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"

