# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=               dotnet-sdk-${VERSION}
VERSION=                2.0.2
PKGNAME=		dotnet-sdk2-${VERSION}
# PKGREVISION=          1
CATEGORIES=             lang
DISTFILES=		dotnet-sdk-2.0.2-linux-x64.tar.gz

SITES.dotnet-sdk-2.0.2-linux-x64.tar.gz=	https://download.microsoft.com/download/7/3/A/73A3E4DC-F019-47D1-9951-0453676E059B/

MAINTAINER=             pkgsrc-users@NetBSD.org
HOMEPAGE=               https://www.microsoft.com/net/
COMMENT=		.NET Core 2.x
LICENSE=                MIT

do-build:

do-install:
	mkdir -p ${DESTDIR}${PREFIX}/share/dotnet
	for i in additionalDeps sdk store; do cp -r ${WRKDIR}/$$i ${DESTDIR}${PREFIX}/share/dotnet; done

DEPENDS+=	dotnet-core2>=2.0:../../base/dotnet-core2

.include "../../mk/bsd.pkg.mk"
