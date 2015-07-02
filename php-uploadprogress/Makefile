# $NetBSD: Makefile,v 1.3 2012/10/28 06:30:58 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
#

MODNAME=		uploadprogress
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES=		www

MAINTAINER=		mbowie@buzmo.com
COMMENT=		PHP extension to track progress of a file upload

CONFIGURE_ARGS+=	--enable-${MODNAME}

.include "../../base/php/extension_versions.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
