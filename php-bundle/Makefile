# $NetBSD: Makefile,v 1.1 2013/07/29 16:46:49 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		${PHP_PKG_PREFIX}-bundle-${PHP_BASE_VERS}
PB_PKGBASE=		${PHP_PKG_PREFIX}-bundle
VERSION=		${PHP_BASE_VERS}
CATEGORIES=		meta-pkgs www
META_PACKAGE=		yes
MASTER_SITES=		# empty
DISTFILES=		# empty


MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://www.php.net/
COMMENT=		"meta-package" for the PHP 5.x HTML-embedded scripting language

.include "../../base/php/phpversion.mk"

DEPENDS+=	php>=${PHP_BASE_VERS}<${PHP_NEXT_VERS}:${PHPPKGSRCDIR}
DEPENDS+=	${APACHE_PKG_PREFIX}-${PHP_PKG_PREFIX}>=${PHP_BASE_VERS}:../../base/ap-php
DEPENDS+=	${APACHE_PKG_PREFIX}-cloudflare>=0.0.1:../../base/ap-cloudflare
.if ${OPSYS} != Linux
DEPENDS+=	${APACHE_PKG_PREFIX}-usdt>=20130730:../../base/ap2-usdt
.endif
DEPENDS+=	${APACHE_PKG_PREFIX}-xsendfile>=0.12:../../base/ap2-xsendfile

.include "../../base/${PHP_PKG_PREFIX}/extensions.mk"

.include "../../base/php/extension_versions.mk"

.for extension in ${PHP_EXTENSION_LIST}

.if exists(../../base/php-${extension}/depends.mk)
.include "../../base/php-${extension}/depends.mk"
.endif

DEPENDS+=	${PHP_PKG_PREFIX}-${extension}>=${PHP_EXTENSION_VERSION.${extension}}:../../base/php-${extension}

.endfor

.if defined(PHP_BUNDLE_PATCH)
PKGREVISION=		${PHP_BUNDLE_PATCH}
.endif

.include "../../base/apache/apache.mk"
.include "../../mk/bsd.pkg.mk"