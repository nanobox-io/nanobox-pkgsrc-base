# $NetBSD: Makefile,v 1.1 2015/02/23 16:11:05 leot1990 Exp $
#

VERSION=	2.1.1
DISTNAME=	phantomjs-${VERSION}-linux-x86_64
PKGNAME=	phantomjs-${VERSION}
CATEGORIES=	www
MASTER_SITES=	https://bitbucket.org/ariya/phantomjs/downloads/
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	braxton@nanobox.io
HOMEPAGE=	http://www.phantomjs.org/
COMMENT=	Headless WebKit with JavaScript API
LICENSE=	modified-bsd

do-build:
	patchelf --set-rpath ${PREFIX}/lib ${WRKSRC}/bin/phantomjs 

do-install:
	mkdir -p ${DESTDIR}${PREFIX}
	cp -r ${WRKSRC}/bin ${DESTDIR}${PREFIX}
	mkdir -p ${DESTDIR}${PREFIX}/share/examples
	cp -r ${WRKSRC}/examples ${DESTDIR}${PREFIX}/share/examples/phantomjs

BUILD_DEPENDS+=	patchelf>=0.9:../../devel/patchelf

.include "../../fonts/fontconfig/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
