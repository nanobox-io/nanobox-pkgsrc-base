# $NetBSD: Makefile,v 1.23 2013/03/17 10:46:45 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		xhprof
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		sysutils

MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		function-level hierarchical profiler for PHP
LICENSE=		php


CONFLICTS=		php-xhprof-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
WRKSRC=			${WRKDIR}/xhprof-${PECL_VERSION}/extension

PLIST_SRC+=		${.CURDIR}/PLIST.extras
PLIST_SUBST+=		PKGBASE=${PKGBASE:Q}

.include "../../base/php/extension_versions.mk"

#.if ${_PHP_VERSION} == "70" || ${_PHP_VERSION} == "71"
#DISTINFO_FILE=		${.CURDIR}/distinfo-php70
#.endif

.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
