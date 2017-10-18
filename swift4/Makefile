# $NetBSD: Makefile,v 1.1 2015/02/23 16:11:05 leot1990 Exp $
#

VERSION=	4.0
DISTNAME=	swift-${VERSION}-RELEASE-ubuntu16.04
PKGNAME=	swift-${VERSION}
CATEGORIES=	lang
MASTER_SITES=	https://swift.org/builds/swift-${VERSION}-release/ubuntu1604/swift-${VERSION}-RELEASE/

MAINTAINER=	braxton@nanobox.io
HOMEPAGE=	http://swift.org
COMMENT=	Swift 4.0 language package
LICENSE=	apache-2.0

NO_BUILD=	true

do-install:
	mkdir -p ${DESTDIR}${PREFIX}
	for i in bin include lib libexec local share; do \
		cp -r ${WRKSRC}/usr/$$i ${DESTDIR}${PREFIX}; \
	done

.include "../../lang/python27/buildlink3.mk"
.include "../../base/icu-55/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"

