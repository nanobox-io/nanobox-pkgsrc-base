# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
PKGNAME=		${PHP_PKG_PREFIX}-newrelic-${NEWRELIC_VERSION}
DISTNAME=		newrelic-php5-${NEWRELIC_VERSION}-${OS}
PKGBASE=		${PHP_PKG_PREFIX}-newrelic
VERSION=		${NEWRELIC_VERSION}
CATEGORIES=		pagoda
MASTER_SITES=		https://download.newrelic.com/php_agent/release/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://download.newrelic.com/php_agent/release/
COMMENT=		Newrelic php package
#LICENSE=		# TODO: (see mk/license.mk)

USE_LANGUAGES=		# none

.include "../../mk/bsd.prefs.mk"
.include "../../base/php/phpversion.mk"
.include "../../base/newrelic/newrelicversion.mk"


.if ${OPSYS} == Linux
OS=			linux
.elif ${OPSYS} == SunOS	
OS=			solaris
.else
PKG_SKIP_REASON+=	"Operating system not supported"
.endif

.if ${ABI} == 64
  SYSARCH= x64
.else
  SYSARCH= x86
.endif

.if exists(${LOCALBASE}/lib/php/20170718)
PHPAPI=			20170718
.elif exists(${LOCALBASE}/lib/php/20160303)
PHPAPI=			20160303
.elif exists(${LOCALBASE}/lib/php/20151012)
PHPAPI=			20151012
.elif exists(${LOCALBASE}/lib/php/20131226)
PHPAPI=			20131226
.elif exists(${LOCALBASE}/lib/php/20121212)
PHPAPI=			20121212
.elif exists(${LOCALBASE}/lib/php/20100525)
PHPAPI=			20100525
.elif exists(${LOCALBASE}/lib/php/20090626)
PHPAPI=			20090626
.elif exists(${LOCALBASE}/lib/php/20060613)
PHPAPI=			20060613
.elif exists(${LOCALBASE}/lib/php/20050922)
PHPAPI=			20050922
.endif

PLIST_SUBST+=		PHPAPI=${PHPAPI}

do-build:
	echo "Nothing to build"

do-install:
	mkdir -p ${DESTDIR}${PREFIX}/lib/php/${PHPAPI}/
	cp ${WRKSRC}/agent/${SYSARCH}/newrelic-${PHPAPI}.so ${DESTDIR}${PREFIX}/lib/php/${PHPAPI}/newrelic.so

.include "${PHPPKGSRCDIR}/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
