# $NetBSD: Makefile,v 1.23 2013/03/17 10:46:45 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		json_post
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		devel

MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		json_post extension
LICENSE=		php

CONFLICTS=		php-json_post-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
WRKSRC=			${WRKDIR}/json_post-${PECL_VERSION}

.include "../../base/php/extension_versions.mk"
.include "../../base/php/ext.mk"
.include "../../base/php-json/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"