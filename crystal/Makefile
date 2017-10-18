# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=               ${VERSION}
VERSION=                0.23.1
EXTRA_NUMBER=		3
PKGNAME=		crystal-${VERSION}
# PKGREVISION=          1
CATEGORIES=             lang
DIST_SUBDIR=		crystal
DISTFILES=		crystal-${VERSION}-${EXTRA_NUMBER}-linux-x86_64.tar.gz

SITES.crystal-${VERSION}-${EXTRA_NUMBER}-linux-x86_64.tar.gz= https://github.com/crystal-lang/crystal/releases/download/${VERSION}/

MAINTAINER=             pkgsrc-users@NetBSD.org
HOMEPAGE=               https://github.com/crystal-lang/crystal
COMMENT=                Crystal language
LICENSE=                apache-2.0

WRKSRC=			${WRKDIR}/crystal-${VERSION}-${EXTRA_NUMBER}

do-build:
	ln -sf libyaml-0.so.2.0.4 ${WRKSRC}/embedded/lib/libyaml.so
	ln -sf libyaml-0.so.2.0.4 ${WRKSRC}/embedded/lib/libyaml-0.so.2
	patchelf --set-rpath ${PREFIX}/crystal/embedded/lib ${WRKSRC}/embedded/bin/shards

do-install:
	mkdir -p ${DESTDIR}${PREFIX}/crystal
	cp -a ${WRKSRC}/* ${DESTDIR}${PREFIX}/crystal/
	mkdir -p ${DESTDIR}${PREFIX}/bin
	ln -sf ${PREFIX}/crystal/bin/crystal ${DESTDIR}${PREFIX}/bin/crystal

BUILD_DEPENDS+=	patchelf>=0.9:../../devel/patchelf

.include "../../mk/bsd.pkg.mk"
