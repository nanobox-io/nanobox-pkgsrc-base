# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=               dotnet-core-${VERSION}
VERSION=                2.0.0
PKGNAME=		dotnet-core2-${VERSION}
# PKGREVISION=          1
CATEGORIES=		lang
DISTFILES=		dotnet-runtime-2.0.0-linux-x64.tar.gz

SITES.dotnet-runtime-2.0.0-linux-x64.tar.gz=	https://download.microsoft.com/download/5/F/0/5F0362BD-7D0A-4A9D-9BF9-022C6B15B04D/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://www.microsoft.com/net/
COMMENT=		.NET Core 2.x
LICENSE=		MIT

do-build:
	cd ${WRKDIR}/shared/Microsoft.NETCore.App/2.0.0; \
	for i in System.Net.Http.Native.so libcoreclrtraceptprovider.so System.Globalization.Native.so libclrjit.so libcoreclr.so libdbgshim.so libmscordaccore.so; do \
		patchelf --set-rpath ${PREFIX}/lib $$i; \
	done 

do-install:
	mkdir -p ${DESTDIR}${PREFIX}/share/dotnet
	for i in host shared; do cp -r ${WRKDIR}/$$i ${DESTDIR}${PREFIX}/share/dotnet; done

BUILD_DEPENDS+=	patchelf>=0.9:../../devel/patchelf

DEPENDS+=	dotnet-bin>=2.0.0:../../base/dotnet-bin

.include "../../base/icu-55/buildlink3.mk"
.include "../../base/nongnu-libunwind/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../base/lttng-ust/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
