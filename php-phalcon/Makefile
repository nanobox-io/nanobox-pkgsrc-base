# $NetBSD: Makefile,v 1.1 2013/03/05 22:18:37 imil Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		phalcon
CATEGORIES+=		www
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
# PECL_LEGACY_VERSION_SCHEME=	yes

HOMEPAGE=		http://phalconphp.com/
COMMENT=		Phalcon is a web framework implemented as a C extension offering high performance and lower resource consumption
LICENSE=		php

DOCDIR=			${PREFIX}/share/doc
INSTALLATION_DIRS=	${DOCDIR}

.include "../../base/php/extension_versions.mk"

GIT_REPOSITORIES=	phalcon
GIT_REPO.phalcon=	git://github.com/phalcon/cphalcon.git
.if ${_PHP_VERSION} == "53" || ${_PHP_VERSION} == "54"
GIT_TAG.phalcon=	phalcon-v${PECL_VERSION}
.else
GIT_TAG.phalcon=	v${PECL_VERSION}
.endif

WRKSRC=			${WRKDIR}/phalcon/ext

USE_LANGUAGES+=		c c++

USE_TOOLS+=		gmake
CFLAGS+=		-O2 -Wall -fvisibility=hidden -flto -DZEPHIR_RELEASE=1

.if ${PKG_PHP_MAJOR_VERS} == "7"
EXTENSIONS=		phar json filter hash gmp ctype pdo pdo_sqlite simplexml tokenizer xmlwriter dom zip mbstring xml zephir_parser

.for extension in ${EXTENSIONS}

.if exists(../../base/php-${extension}/depends.mk)
.include "../../base/php-${extension}/depends.mk"
.endif

BUILD_DEPENDS+=	${PHP_PKG_PREFIX}-${extension}>=${PHP_EXTENSION_VERSION.${extension}}:../../base/php-${extension}

BUILD_DEPENDS+=	composer>=1.2.1:../../base/composer
BUILD_DEPENDS+=	re2c>=0.15.3:../../devel/re2c

.endfor

PHALCONDIR= ${WRKDIR}/phalcon

pre-configure:
	if [ ! -f ${PREFIX}/etc/php.ini ]; then sudo cp ${PREFIX}/etc/php/php.ini ${PREFIX}/etc/php.ini; fi
	sudo cp ${PREFIX}/etc/php.ini ${PREFIX}/etc/php/php.ini
	for i in ${EXTENSIONS}; do echo "extension=$${i}.so" >> ${PREFIX}/etc/php/php.ini; done
	cd ${PHALCONDIR}; composer install
	cd ${PHALCONDIR}; composer require "phalcon/zephir:dev-master"
	cd ${PHALCONDIR}; vendor/bin/zephir generate -backend=ZendEngine3
	cd ${WRKSRC}; phpize

.endif

.include "../../base/php/ext.mk"
.include "../../base/php-pdo/buildlink3.mk"
.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"
