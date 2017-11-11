# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=               dotnet-core-${VERSION}
VERSION=                1.1.4
PKGNAME=		dotnet-core-${VERSION}
# PKGREVISION=          1
CATEGORIES=             lang
DISTFILES=		dotnet-ubuntu.16.04-x64.1.1.4.tar.gz

SITES.dotnet-ubuntu.16.04-x64.1.1.4.tar.gz=	https://download.microsoft.com/download/6/F/B/6FB4F9D2-699B-4A40-A674-B7FF41E0E4D2/

MAINTAINER=             pkgsrc-users@NetBSD.org
HOMEPAGE=               https://www.microsoft.com/net/download/linux
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

.include "../../lang/libunwind/buildlink3.mk"
.include "../../devel/lldb/buildlink3.mk"
.include "../../base/icu-55/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
