# $NetBSD: Makefile,v 1.4 2012/10/25 06:56:45 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		json
CATEGORIES+=		textproc
COMMENT=		PHP extension for JSON serialization support

CONFIGURE_ARGS+=	--enable-${MODNAME}=shared

.include "../../base/php/ext.mk"

INSTALLATION_DIRS+=	include/php/ext/json

JSON_INCLUDES=		php_json.h
PLIST_SRC+=		${.CURDIR}/../../base/php-json/PLIST.json

post-install:
.for inc in ${JSON_INCLUDES}
	${INSTALL_DATA} ${WRKSRC}/${inc} ${DESTDIR}${PREFIX}/include/php/ext/json/${inc}
.endfor

.include "../../mk/bsd.pkg.mk"
