# $NetBSD: Makefile,v 1.11 2012/10/23 17:18:58 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		sockets
CATEGORIES+=		net
COMMENT=		PHP extension for sockets support

CONFLICTS=		php-sockets-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}=shared,${BUILDLINK_DIR}

.include "../../mk/bsd.prefs.mk"

.if ${OPSYS} == "SunOS"
CONFIGURE_ARGS+=	ac_cv_func_if_indextoname=yes
.endif

.include "../../base/php/ext.mk"

.if ${PKG_PHP_VERSION} == 53
.else
CFLAGS_SOCKETS.SunOS+= -D_XOPEN_SOURCE -D_XOPEN_SOURCE_EXTENDED
CPPFLAGS.SunOS+= -D_XPG4_2
.endif

LIBS.SunOS+= 		-lxnet

.include "../../mk/bsd.pkg.mk"
