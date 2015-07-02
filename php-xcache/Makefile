# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
#

MODNAME=		xcache
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
# PKGNAME=		${MODNAME}-${PECL_VERSION}
CATEGORIES=		www
MASTER_SITES=		http://xcache.lighttpd.net/pub/Releases/${PECL_VERSION}/
EXTRACT_SUFX=		.tar.gz # required, because ../../base/php/ext.mk
				# overrides it with .tgz

# Original Maintainer (since dec 2010)
#MAINTAINER=		mbowie@buzmo.com
# Maintainer from dec 2010 on
MAINTAINER=		vs@nifelheim.info
HOMEPAGE=		http://xcache.lighttpd.net/
COMMENT=		Fast and stable PHP opcode cacher

PLIST_SRC+=		PLIST

CONFIGURE_ARGS+=	--enable-${MODNAME}

.include "../../mk/bsd.prefs.mk"
.include "options.mk"

INSTALLATION_DIRS=	share/examples/xcache
INSTALLATION_DIRS+=	share/xcache
INSTALLATION_DIRS+=	share/xcache/admin
INSTALLATION_DIRS+=	share/xcache/coverager

do-install:
	${INSTALL_DATA} ${WRKSRC}/xcache.ini \
		${DESTDIR}${PREFIX}/share/examples/xcache/
	cp -r ${WRKSRC}/htdocs \
		${DESTDIR}${PREFIX}/share/xcache

.include "../../base/php/extension_versions.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
