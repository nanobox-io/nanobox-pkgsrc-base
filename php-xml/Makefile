# $NetBSD: Makefile,v 1.2 2012/10/08 13:04:27 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		xml
CATEGORIES+=		textproc
COMMENT=		PHP extension for xml conversion support
PKGREVISION?=		3

CONFLICTS=		php-xml-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
CONFIGURE_ARGS+=	--with-libxml-dir=${BUILDLINK_PREFIX.libxml2}
CONFIGURE_ARGS+=	--with-libexpat-dir=${BUILDLINK_PREFIX.expat}

CPPFLAGS+=  		-I${WRKDIR}/${DISTNAME}

.include "../../base/php/ext.mk"

INSTALLATION_DIRS+=	include/php/ext/xml

XML_INCLUDES=		expat_compat.h php_xml.h
PLIST_SRC+=		${.CURDIR}/../../base/php-xml/PLIST.xml

post-install:
.for inc in ${XML_INCLUDES}
	${INSTALL_DATA} ${WRKSRC}/${inc} ${DESTDIR}${PREFIX}/include/php/ext/xml/${inc}
.endfor

.include "../../textproc/libxml2/buildlink3.mk"
.include "../../textproc/expat/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"