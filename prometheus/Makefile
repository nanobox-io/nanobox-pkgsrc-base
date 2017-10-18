# $NetBSD: Makefile,v 1.1 2015/02/23 16:11:05 leot1990 Exp $
#

VERSION=	1.7.2
DISTNAME=	prometheus-${VERSION}.linux-amd64
PKGNAME=	prometheus-${VERSION}
CATEGORIES=	www
MASTER_SITES=	https://github.com/prometheus/prometheus/releases/download/v${VERSION}/
EXTRACT_SUFX=	.tar.gz

MAINTAINER=	braxton@nanobox.io
HOMEPAGE=	http://prometheus.io
COMMENT=	metrics and alerting
LICENSE=	apache-2.0

BIN_FILES=	prometheus promtool
ETC_FILES=	prometheus.yml
LIB_FILES=	console_libraries consoles	

NO_BUILD=	yes

do-install:
	for i in /bin /etc /lib/prometheus; do \
		mkdir -p ${DESTDIR}${PREFIX}$${i}; \
	done
	for i in ${BIN_FILES}; do \
		cp -r ${WRKSRC}/$${i} ${DESTDIR}${PREFIX}/bin; \
	done
	for i in ${ETC_FILES}; do \
		cp -r ${WRKSRC}/$${i} ${DESTDIR}${PREFIX}/etc; \
	done
	for i in ${LIB_FILES}; do \
		cp -r ${WRKSRC}/$${i} ${DESTDIR}${PREFIX}/lib/prometheus; \
	done

.include "../../mk/bsd.pkg.mk"
