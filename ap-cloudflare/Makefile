# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
#  # vim: ts=8 sw=8 ft=make noet

VERSION=		0.0.1
DISTNAME=		mod_cloudflare
PKGNAME=		${APACHE_PKG_PREFIX}-${DISTNAME:S/mod_//}-${VERSION}
CATEGORIES=		www
MASTER_SITES=		https://www.cloudflare.com/static/misc/mod_cloudflare/
EXTRACT_SUFX=		.c

MAINTAINER=		braxton@pagodabox.com
HOMEPAGE=		https://www.cloudflare.com/resources-downloads
COMMENT=		Apache 2 module for cloudflare
LICENSE=		apache-2.0

APACHE_MODULE=		YES
APACHE_MODULE_NAME=	${DISTNAME:C|-.*||}.so
APACHE_MODULE_SRC=	${DISTNAME:C|-.*||}.c
APACHE_MODULE_LA=	${DISTNAME:C|-.*||}.la

PKG_APACHE_ACCEPTED=	apache2 apache22 apache24

do-extract:
	mkdir ${WRKSRC}
	cd ${WRKSRC} && cp ${DISTDIR}/${DISTFILES} .

do-build:
	cd ${WRKSRC} && ${APXS} ${CPPFLAGS} ${LDFLAGS} -c -o ${APACHE_MODULE_NAME} ${APACHE_MODULE_SRC}

do-install:
	${INSTALL_LIB_DIR} ${DESTDIR}${PREFIX}/lib/httpd
	cd ${WRKSRC} && ${APXS} -i -S LIBEXECDIR=${DESTDIR}${PREFIX}/lib/httpd ${APACHE_MODULE_LA}

.include "../../base/apache/apache.mk"
.include "../../mk/bsd.pkg.mk"
