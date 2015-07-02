# $NetBSD: Makefile,v 1.10 2012/10/31 11:19:24 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		sysvshm
CATEGORIES+=		devel
COMMENT=		PHP extension for SysV shared memory support

CONFLICTS=		php-sysvshm-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}=shared,${BUILDLINK_DIR}

.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
