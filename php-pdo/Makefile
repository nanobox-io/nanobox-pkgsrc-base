# $NetBSD: Makefile,v 1.12 2012/10/02 21:25:39 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
MODNAME=		pdo
CATEGORIES+=		databases
COMMENT=		PHP extension for PHP Data Objects (base)

USE_PHP_EXT_PATCHES=	yes

.include "../../mk/bsd.prefs.mk"

.include "../../base/php/ext.mk"

CONFIGURE_ARGS+=	--with-${MODNAME}

INSTALLATION_DIRS+=	include/php/ext/pdo

.if ${PKG_PHP_VERSION} == 70 || ${PKG_PHP_VERSION} == 71 || ${PKG_PHP_VERSION} == 72
PDO_INCLUDES=		php_pdo_driver.h  php_pdo_error.h  php_pdo_int.h  php_pdo.h
PLIST_SRC+=		${.CURDIR}/../../base/php-pdo/PLIST.pdo70
.elif ${PKG_PHP_VERSION} == 56
PDO_INCLUDES=		php_pdo_driver.h php_pdo.h php_pdo_error.h
PLIST_SRC+=		${.CURDIR}/../../base/php-pdo/PLIST.pdo56
.else
PDO_INCLUDES=		php_pdo_driver.h php_pdo.h
PLIST_SRC+=		${.CURDIR}/../../base/php-pdo/PLIST.pdo
.endif

post-install:
.for inc in ${PDO_INCLUDES}
	${INSTALL_DATA} ${WRKSRC}/${inc} ${DESTDIR}${PREFIX}/include/php/ext/pdo/${inc}
.endfor

.include "../../mk/bsd.pkg.mk"
