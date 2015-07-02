# $NetBSD: Makefile,v 1.6 2012/10/23 17:18:58 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		soap
CATEGORIES+=		net
COMMENT=		PHP extension for SOAP functions

MAINTAINER=		pkgsrc-users@NetBSD.org

CONFLICTS=		php-soap-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
CONFIGURE_ARGS+=	--with-libxml-dir=${BUILDLINK_PREFIX.libxml2}

.include "../../base/php/ext.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
