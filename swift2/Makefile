# $NetBSD: Makefile,v 1.1 2015/02/23 16:11:05 leot1990 Exp $
#

VERSION=	2.2.1
DISTNAME=	swift-${VERSION}-RELEASE-ubuntu15.10
PKGNAME=	swift-${VERSION}
CATEGORIES=	lang
MASTER_SITES=	https://swift.org/builds/swift-${VERSION}-release/ubuntu1510/swift-${VERSION}-RELEASE/

MAINTAINER=	braxton@nanobox.io
HOMEPAGE=	http://swift.org
COMMENT=	Swift 2.x language package
LICENSE=	apache-2.0

do-build:
	patchelf --set-rpath "\$$ORIGIN/../lib/swift/linux" ${WRKSRC}/usr/bin/repl_swift
	patchelf --set-rpath "\$$ORIGIN:${PREFIX}/lib/swift/linux:${PREFIX}/lib" ${WRKSRC}/usr/lib/swift/linux/libswiftCore.so
	patchelf --set-rpath "\$$ORIGIN:${PREFIX}/lib/swift/linux:${PREFIX}/lib" ${WRKSRC}/usr/lib/swift/linux/libswiftGlibc.so

do-install:
	mkdir -p ${DESTDIR}${PREFIX}
	for i in bin include lib share; do \
		cp -r ${WRKSRC}/usr/$$i ${DESTDIR}${PREFIX}; \
	done

BUILD_DEPENDS+=	patchelf>=0.9:../../devel/patchelf

.include "../../lang/python27/buildlink3.mk"
.include "../../base/icu-55/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"

