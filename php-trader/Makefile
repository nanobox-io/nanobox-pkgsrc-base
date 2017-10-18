# $NetBSD: Makefile,v 1.23 2013/03/17 10:46:45 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		trader
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		devel

MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		trader extension
LICENSE=		2-clause-bsd

CONFIGURE_ARGS+=	--enable-${MODNAME}

.include "../../base/php/extension_versions.mk"

.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
