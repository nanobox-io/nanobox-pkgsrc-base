# $NetBSD: Makefile,v 1.16 2012/10/23 17:18:58 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		xmlrpc
CATEGORIES+=		net
COMMENT=		PHP extension for XML-RPC support

CONFLICTS=		php-xmlrpc-[0-9]*

HOMEPAGE=		http://xmlrpc-epi.sourceforge.net/

USE_PHP_EXT_PATCHES=	YES
CONFIGURE_ARGS+=	--enable-${MODNAME}=shared,${BUILDLINK_DIR}

.include "../../base/php/phpversion.mk"

CONFIGURE_ARGS+=	--with-libxml-dir=${BUILDLINK_PREFIX.libxml2}

.include "../../converters/libiconv/buildlink3.mk"

# This is necessary so that PHP would find either the libc iconv
# or use the packaged iconv, as appropriate; using
# --with-iconv=shared,${BUILDLINK_PREFIX.iconv} assumes libiconv exists
#
CHECK_BUILTIN.iconv:=	yes
.include "../../converters/libiconv/builtin.mk"
CHECK_BUILTIN.iconv:=	no

.if !empty(USE_BUILTIN.iconv:M[nN][oO])
CONFIGURE_ARGS+=	--with-iconv-dir=${BUILDLINK_PREFIX.iconv}
.else
CONFIGURE_ARGS+=	--with-iconv-dir
.endif

.include "../../base/php-xml/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
