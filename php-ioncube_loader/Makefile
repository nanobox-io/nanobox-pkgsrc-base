# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

PKGNAME=		${PHP_PKG_PREFIX}-ioncube-${PHP_EXTENSION_VERSION.${MODNAME}}
DISTNAME=		phpd-4.6-libs-smartos-20140806
MODNAME=		ioncube_loader
VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		devel
MASTER_SITES=		http://downloads3.ioncube.com/loader_downloads/
EXTRACT_SUFX=		.tgz

MAINTAINER=		filip@joyent.com
COMMENT=		PHP ionCube Encoder

PKG_DESTDIR_SUPPORT=	user-destdir

NO_CHECKSUM=		yes
NO_BUILD=		yes
NO_CONFIGURE=		yes
EXTRACT_ELEMENTS=	# empty
WRKSRC=			${WRKDIR}
MODULESDIR=		${WRKSRC}
INSTALLATION_DIRS+=	share/examples/ioncube
PLIST_SRC=		${.CURDIR}/PLIST

post-patch:
	cp -r ${WRKSRC}/${PKG_PHP_VERSION:C/([0-9])([0-9])/\1.\2/}.0/ioncube_loader_4.6.so  \
		${WRKSRC}/${MODNAME}.so

.include "../../base/php/extension_versions.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
