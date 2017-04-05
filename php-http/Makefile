# $NetBSD: Makefile,v 1.23 2013/03/17 10:46:45 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		http
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
PECL_DISTNAME=		pecl_http-${PECL_VERSION}
CATEGORIES+=		www

MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		Extended HTTP Support
LICENSE=		php


CONFLICTS=		php-http-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
CONFIGURE_ARGS+=	--with-http-zlib-dir=${BUILDLINK_PREFIX.zlib}
CONFIGURE_ARGS+=	--with-http-curl-dir=${BUILDLINK_PREFIX.curl}
CONFIGURE_ARGS+=	--with-http-libevent-dir=${BUILDLINK_PREFIX.libevent}
CONFIGURE_ARGS+=	--with-http-libidn-dir=${BUILDLINK_PREFIX.libidn}

WRKSRC=			${WRKDIR}/pecl_http-${PECL_VERSION}

PLIST_SRC+=		${.CURDIR}/PLIST.extras
PLIST_SUBST+=		PKGBASE=${PKGBASE:Q}

pre-configure:
	sudo bash -c "echo extension=raphf.so >> ${PREFIX}/etc/php/php.ini"
	sudo bash -c "echo extension=propro.so >> ${PREFIX}/etc/php/php.ini"

.include "../../base/php/extension_versions.mk"

.if ${_PHP_VERSION} == "70" || ${_PHP_VERSION} == "71"
DISTINFO_FILE=		${.CURDIR}/distinfo-php70
PATCHDIR=		${.CURDIR}/patches70
.include "../../textproc/icu/buildlink3.mk"
.endif

.include "../../base/php/ext.mk"
.include "../../base/php-propro/buildlink3.mk"
.include "../../base/php-raphf/buildlink3.mk"
.include "../../devel/libevent/buildlink3.mk"
.include "../../devel/libidn/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
