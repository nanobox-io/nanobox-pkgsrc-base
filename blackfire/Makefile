# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

PKGNAME=		blackfire-${VERSION}
VERSION=		1.15.0
PKGREVISION=		1
CATEGORIES=		www
DISTFILES=		blackfire-agent-linux_static_amd64 blackfire-cli-linux_static_amd64
DIST_SUBDIR=		blackfire-${VERSION}
MASTER_SITES=		https://packages.blackfire.io/binaries/blackfire-agent/${VERSION}/

HOMEPAGE=		https://blackfire.io
COMMENT=		PHP Profiling
LICENSE=		#

USE_LANGUAGES=		# none

NO_BUILD=	yes

do-install:
	mkdir -p ${DESTDIR}${PREFIX}/bin/
	cp ${WRKDIR}/blackfire-agent-linux_static_amd64 ${DESTDIR}${PREFIX}/bin/blackfire-agent
	chmod 755 ${DESTDIR}${PREFIX}/bin/blackfire-agent
	cp ${WRKDIR}/blackfire-cli-linux_static_amd64 ${DESTDIR}${PREFIX}/bin/blackfire
	chmod 755 ${DESTDIR}${PREFIX}/bin/blackfire

.include "../../mk/bsd.prefs.mk"
.include "../../mk/bsd.pkg.mk"
