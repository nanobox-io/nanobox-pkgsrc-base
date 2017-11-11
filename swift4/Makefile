# $NetBSD: Makefile,v 1.1 2015/02/23 16:11:05 leot1990 Exp $
#

VERSION=	4.0
PKGREVISION=	1
DISTNAME=	swift-${VERSION}-RELEASE-ubuntu16.04
PKGNAME=	swift-${VERSION}
CATEGORIES=	lang
MASTER_SITES=	https://swift.org/builds/swift-${VERSION}-release/ubuntu1604/swift-${VERSION}-RELEASE/

MAINTAINER=	braxton@nanobox.io
HOMEPAGE=	http://swift.org
COMMENT=	Swift 4.0 language package
LICENSE=	apache-2.0

LLDB_BINS=	lldb-4.0.0 lldb-argdumper lldb-mi-4.0.0 lldb-server-4.0.0 
SWIFT_BINS=	repl_swift swift-build swift-package swift-run swift-test

LIBS_A=		libsourcekitdInProc.so

LIBS_B=		liblldb.so.4.0.0 python2.7/site-packages/lldb/_lldb.so

LIBS_C=		swift/pm/3/libPackageDescription.so swift/pm/4/libPackageDescription.so

LIBS_D=		swift/linux/libswiftSwiftOnoneSupport.so swift/linux/libswiftCore.so swift/linux/libXCTest.so \
		swift/linux/libswiftGlibc.so swift/linux/libFoundation.so swift/linux/libswiftRemoteMirror.so

patch-lldb-bins:
	for i in ${LLDB_BINS}; do \
		patchelf --set-rpath "\$$ORIGIN/../lib:${PREFIX}/lib" ${WRKSRC}/usr/bin/$$i; \
	done

patch-swift-bins:
	for i in ${SWIFT_BINS}; do \
		patchelf --set-rpath "\$$ORIGIN/../lib/swift/linux:\$$ORIGIN:${PREFIX}/lib:${PREFIX}/lib/swift/linux" ${WRKSRC}/usr/bin/$$i; \
	done

patch-libs-a:
	for i in ${LIBS_A}; do \
		patchelf --set-rpath "\$$ORIGIN/../lib/swift/linux:${PREFIX}/lib/swift/linux:${PREFIX}/lib" ${WRKSRC}/usr/lib/$$i; \
	done

patch-libs-b:
	for i in ${LIBS_B}; do \
		patchelf --set-rpath "\$$ORIGIN/../lib:${PREFIX}/lib" ${WRKSRC}/usr/lib/$$i; \
	done

patch-libs-c:
	for i in ${LIBS_C}; do \
		patchelf --set-rpath "\$$ORIGIN/../linux:${PREFIX}/lib" ${WRKSRC}/usr/lib/$$i; \
	done

patch-libs-d:
	for i in ${LIBS_D}; do \
		patchelf --set-rpath "\$$ORIGIN:${PREFIX}/lib/swift/linux:${PREFIX}/lib" ${WRKSRC}/usr/lib/$$i; \
	done

do-build: patch-lldb-bins patch-swift-bins patch-libs-a patch-libs-b patch-libs-c patch-libs-d

do-install:
	mkdir -p ${DESTDIR}${PREFIX}
	for i in bin include lib libexec local share; do \
		cp -r ${WRKSRC}/usr/$$i ${DESTDIR}${PREFIX}; \
	done

BUILD_DEPENDS+=	patchelf>=0.9:../../devel/patchelf

.include "../../lang/python27/buildlink3.mk"
.include "../../base/icu-55/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"

