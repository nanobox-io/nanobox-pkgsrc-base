# $NetBSD: Makefile,v 1.23 2013/03/17 10:46:45 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		propro
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		devel

MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		propro extension
LICENSE=		php


CONFLICTS=		php-propro-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
WRKSRC=			${WRKDIR}/propro-${PECL_VERSION}

PLIST_SRC+=		${.CURDIR}/PLIST.extras
PLIST_SUBST+=		PKGBASE=${PKGBASE:Q}

PROPRO_INCLUDES=	php_propro.h

INSTALLATION_DIRS+=	include/php/ext/propro

post-install:
.for inc in ${PROPRO_INCLUDES}
	${INSTALL_DATA} ${WRKSRC}/${inc} ${DESTDIR}${PREFIX}/include/php/ext/propro/${inc}
.endfor

.include "../../base/php/extension_versions.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"