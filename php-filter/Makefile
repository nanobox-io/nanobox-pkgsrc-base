# $NetBSD: Makefile,v 1.2 2012/10/08 13:04:27 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		filter
CATEGORIES+=		devel
COMMENT=		PHP extension for filter inputs

CONFLICTS=		php-filter-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}

.include "../../base/php/ext.mk"

INSTALLATION_DIRS+=	include/php/ext/filter

FILTER_INCLUDES=	php_filter.h
PLIST_SRC+=		${.CURDIR}/../../base/php-filter/PLIST.filter

post-install:
.for inc in ${FILTER_INCLUDES}
	${INSTALL_DATA} ${WRKSRC}/${inc} ${DESTDIR}${PREFIX}/include/php/ext/filter/${inc}
.endfor

.include "../../mk/bsd.pkg.mk"