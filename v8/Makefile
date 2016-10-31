# $NetBSD: Makefile,v 1.27 2015/12/05 21:25:47 adam Exp $

DISTNAME=	v8-${VERSION}
VERSION=	5.6.113
CATEGORIES=	base
MASTER_SITES=	https://github.com/v8/v8

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/v8/v8
COMMENT=	V8 is Googles open source JavaScript engine.
# LICENSE=	GPL-2
BUILD_DEPENDS+=	depot_tools>=0.0.1:../../base/depot_tools
BUILD_DEPENDS+= python>=2.7:../../base/python27
BUILD_DEPENDS+=         git-base>=1.6.4:../../devel/git-base

USE_TOOLS+=	gmake

USE_LANGUAGES+=	c c++

WRKSRC=${WRKDIR}/v8

DISTFILES?=             # empty

PREPEND_PATH+=	${WRKDIR}/depot_tools

pre-extract:
	cd ${WRKDIR}; git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
	cd ${WRKDIR}; fetch v8

.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
