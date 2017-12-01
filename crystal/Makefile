# $NetBSD: Makefile,v 1.1 2013/03/05 22:18:37 imil Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		crystal-${VERSION}
PKGNAME=		crystal-${VERSION}
#PKGREVISION=		2
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
GIT_TAG.shards=		v${SHARD_VERSION}

WRKSRC=			${WRKDIR}/crystal

BUILD_DEPENDS=		crystal-omnibus>=${VERSION}:../../base/crystal-omnibus

PREPEND_PATH+=		${PREFIX}/crystal-omnibus/bin

TEST_TARGET=		spec

MAKE_FLAGS+=		release=1
MAKE_FLAGS+=		progress=true
MAKE_FLAGS+=		threads=${MAKE_JOBS}
MAKE_FLAGS+=		stats=true
MAKE_FLAGS+=		verbose=true

post-extract:
	cd ${WRKDIR}/shards; crystal deps
	cd ${WRKSRC}; rm -rf .git

post-build:
	cd ${WRKDIR}/shards; ${WRKSRC}/bin/crystal build --release -o bin/shards src/shards.cr --link-flags "-static"

do-install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	mkdir -p ${DESTDIR}${PREFIX}/crystal/bin
	ln -s ${PREFIX}/crystal/bin/crystal ${DESTDIR}${PREFIX}/bin/crystal
	cp -r ${WRKSRC}/bin/crystal ${DESTDIR}${PREFIX}/crystal/bin/crystal
	cp -r ${WRKSRC}/embedded ${DESTDIR}${PREFIX}/crystal/embedded
	cp -r ${WRKSRC}/etc ${DESTDIR}${PREFIX}/crystal/etc
	cp -r ${WRKSRC}/man ${DESTDIR}${PREFIX}/crystal/man
	cp -r ${WRKSRC}/samples ${DESTDIR}${PREFIX}/crystal/samples
	cp -r ${WRKSRC}/scripts ${DESTDIR}${PREFIX}/crystal/scripts
	cp -r ${WRKSRC}/spec ${DESTDIR}${PREFIX}/crystal/spec
	cp -r ${WRKSRC}/src ${DESTDIR}${PREFIX}/crystal/src

post-install:
	cp ${WRKDIR}/shards/bin/shards ${DESTDIR}${PREFIX}/crystal/embedded/bin/shards
	ln -s ${PREFIX}/crystal/embedded/bin/shards ${DESTDIR}${PREFIX}/bin/shards

.include "../../lang/llvm/buildlink3.mk"
.include "../../devel/boehm-gc/buildlink3.mk"
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

