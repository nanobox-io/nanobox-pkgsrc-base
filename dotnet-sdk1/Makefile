# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=               dotnet-core-${VERSION}
VERSION=                1.1.4
PKGNAME=		dotnet-core-${VERSION}
# PKGREVISION=          1
CATEGORIES=             lang
DISTFILES=		dotnet-dev-ubuntu.16.04-x64.1.1.4.tar.gz

SITES.dotnet-dev-ubuntu.16.04-x64.1.1.4.tar.gz=	https://download.microsoft.com/download/F/4/F/F4FCB6EC-5F05-4DF8-822C-FF013DF1B17F/

MAINTAINER=             pkgsrc-users@NetBSD.org
HOMEPAGE=               https://github.com/crystal-lang/crystal
COMMENT=		.NET Core 1.x
LICENSE=                apache-2.0

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
