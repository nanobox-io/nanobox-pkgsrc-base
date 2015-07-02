# $NetBSD: Makefile,v 1.7 2012/10/25 06:56:46 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		xsl
CATEGORIES+=		textproc
COMMENT=		PHP extension for XSLT functions

CONFLICTS=		php-xsl-[0-9]*

CONFIGURE_ARGS+=	--with-${MODNAME}=shared,${BUILDLINK_PREFIX.libxslt}

# uses symbols from DOM extension, so add explicit depends
DEPENDS+=		${PHP_PKG_PREFIX}-dom-[0-9]*:../../base/php-dom

# build uses includes of the DOM extension, so need to extract that too
EXTRACT_ELEMENTS=	${DISTNAME}/ext/${MODNAME} ${DISTNAME}/ext/dom
WRKSRC=			${WRKDIR}/${DISTNAME}/ext/${MODNAME}

.include "../../base/php/ext.mk"
.include "../../textproc/libxslt/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
