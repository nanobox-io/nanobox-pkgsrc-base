# $NetBSD: Makefile,v 1.1 2013/03/05 22:18:37 imil Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		zephir_parser
CATEGORIES+=		www
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
# PECL_LEGACY_VERSION_SCHEME=	yes

HOMEPAGE=		https://github.com/phalcon/php-zephir-parser
COMMENT=		The Zephir Parser delivered as a C extension for the PHP language.
LICENSE=		mit

DOCDIR=			${PREFIX}/share/doc
INSTALLATION_DIRS=	${DOCDIR}

USE_LANGUAGES+=		c c++

.include "../../base/php/extension_versions.mk"

GIT_REPOSITORIES=	zephir-parser
GIT_REPO.zephir-parser=	git://github.com/phalcon/php-zephir-parser.git
GIT_TAG.zephir-parser=	v${PECL_VERSION}

WRKSRC=			${WRKDIR}/zephir-parser

BUILD_DEPENDS+=	re2c>=0.15.3:../../devel/re2c

${WRKSRC}/parser/lemon:
	cd ${WRKSRC}/parser; gcc lemon.c -o lemon

${WRKSRC}/parser/scanner.c:
	cd ${WRKSRC}/parser; re2c --no-generation-date -o scanner.c scanner.re
	cd ${WRKSRC}/parser; sed s/"\#line"/"\/\/"/g scanner.c > xx && mv -f xx scanner.c

${WRKSRC}/parser/parser.c: ${WRKSRC}/parser/lemon
	cd ${WRKSRC}/parser; ${WRKSRC}/parser/lemon -s parser.php${PKG_PHP_MAJOR_VERS}.lemon
	cd ${WRKSRC}/parser; echo "#include <php.h>" > parser.c
	cd ${WRKSRC}/parser; cat parser.php${PKG_PHP_MAJOR_VERS}.c >> parser.c
	cd ${WRKSRC}/parser; cat base.c >> parser.c
	cd ${WRKSRC}/parser; sed s/"#line"/"\/\/"/g parser.c > xx && mv -f xx parser.c

pre-configure: ${WRKSRC}/parser/scanner.c ${WRKSRC}/parser/parser.c

.include "../../base/php/ext.mk"
.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"
