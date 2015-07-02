# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

PKGNAME= 		newrelic-${NEWRELIC_VERSION}
VERSION=		${NEWRELIC_VERSION}
DISTNAME=		newrelic-php5-${NEWRELIC_VERSION}-solaris
CATEGORIES=		pagoda
MASTER_SITES=		https://download.newrelic.com/php_agent/release/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://download.newrelic.com/php_agent/release/
COMMENT=		Newrelic php package
#LICENSE=		# TODO: (see mk/license.mk)

USE_LANGUAGES=		# none

.include "../../mk/bsd.prefs.mk"
.include "../../base/newrelic/newrelicversion.mk"

.if ${ABI} == 64
  SYSARCH= 		x64
.else
  SYSARCH= 		x86
.endif

do-build:
	echo "Nothing to build"

do-install:
	mkdir -p ${DESTDIR}${PREFIX}/bin/
	cp ${WRKSRC}/daemon/newrelic-daemon.${SYSARCH} ${DESTDIR}${PREFIX}/bin/newrelic-daemon

.include "../../mk/bsd.pkg.mk"
