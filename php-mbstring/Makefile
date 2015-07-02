# $NetBSD: Makefile,v 1.3 2012/10/03 00:20:15 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		mbstring
CATEGORIES+=		converters
COMMENT=		PHP extension for multibyte characters support
LICENSE=		php

CONFLICTS=		php-mbstring-[0-9]*

INSTALLATION_DIRS+=	${PREFIX}/include/php/ext/mbstring
INSTALLATION_DIRS+=	${PREFIX}/include/php/ext/mbstring/libmbfl
INSTALLATION_DIRS+=	${PREFIX}/include/php/ext/mbstring/libmbfl/filters
INSTALLATION_DIRS+=	${PREFIX}/include/php/ext/mbstring/libmbfl/mbfl
INSTALLATION_DIRS+=	${PREFIX}/include/php/ext/mbstring/libmbfl/nls

.include "../../base/php/phpversion.mk"

PLIST_SRC+=		${.CURDIR}/PLIST.libmbfl${PKG_PHP_VERSION}

CONFIGURE_ARGS+=	--enable-${MODNAME}=shared,${BUILDLINK_DIR}

post-install:
	${INSTALL_DATA} ${WRKSRC}/libmbfl/filters/*.h ${DESTDIR}${PREFIX}/include/php/ext/mbstring/libmbfl/filters
	${INSTALL_DATA} ${WRKSRC}/libmbfl/mbfl/*.h ${DESTDIR}${PREFIX}/include/php/ext/mbstring/libmbfl/mbfl
	${INSTALL_DATA} ${WRKSRC}/libmbfl/nls/*.h ${DESTDIR}${PREFIX}/include/php/ext/mbstring/libmbfl/nls

.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"