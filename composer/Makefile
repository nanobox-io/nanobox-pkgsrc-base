# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

VERSION=		1.1.2
DISTNAME=		composer-${VERSION}
PKGNAME=		composer-${VERSION:S/-//}
CATEGORIES=		pagoda
MASTER_SITES=		http://getcomposer.org/download/${VERSION}/
EXTRACT_SUFX=		.phar

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://getcomposer.org/download/
COMMENT=		Dependency Manager for PHP
LICENSE=		MIT

WRKSRC=			${WRKDIR}
USE_LANGUAGES=		# none

EXTRACT_ONLY= 		#

NO_CONFIGURE= 		yes
NO_BUILD= 		yes
INSTALL_UNSTRIPPED= 	yes
INSTALLATION_DIRS+=	bin

# BUILD_DEPENDS+=		php>=5.3.27:../../base/php53

pre-fetch:
	if [ ! -f ${_DISTDIR}${DISTNAME}.phar ]; then \
		${_FETCH_CMD.${FETCH_USING}} ${_FETCH_BEFORE_ARGS.${FETCH_USING}} ${_FETCH_OUTPUT_ARGS.${FETCH_USING}} ${_DISTDIR}${DISTNAME}.phar "${MASTER_SITES}composer.phar" ${_FETCH_AFTER_ARGS.${FETCH_USING}}; \
	fi;

do-install:
	${INSTALL_PROGRAM} ${DISTDIR}/${DISTNAME}.phar ${DESTDIR}${PREFIX}/bin/composer

.include "../../mk/bsd.pkg.mk"
