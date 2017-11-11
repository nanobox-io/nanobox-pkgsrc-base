# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=               dotnet-core-${VERSION}
VERSION=                2.0.0
PKGNAME=		dotnet-bin-${VERSION}
# PKGREVISION=          1
CATEGORIES=		lang
DISTFILES=		dotnet-runtime-2.0.0-linux-x64.tar.gz

SITES.dotnet-runtime-2.0.0-linux-x64.tar.gz=	https://download.microsoft.com/download/5/F/0/5F0362BD-7D0A-4A9D-9BF9-022C6B15B04D/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://www.microsoft.com/net/
COMMENT=		.NET Core 2.x
LICENSE=		MIT

do-build:

do-install:
	mkdir -p ${DESTDIR}${PREFIX}/share/dotnet
	for i in dotnet LICENSE.txt ThirdPartyNotices.txt; do cp ${WRKDIR}/$$i ${DESTDIR}${PREFIX}/share/dotnet; done
	mkdir -p ${DESTDIR}${PREFIX}/bin
	ln -s ../share/dotnet/dotnet ${DESTDIR}${PREFIX}/bin/dotnet

BUILD_DEPENDS+=	patchelf>=0.9:../../devel/patchelf

.include "../../mk/bsd.pkg.mk"
