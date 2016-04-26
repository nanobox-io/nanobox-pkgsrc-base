# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

PKGNAME=		${PHP_PKG_PREFIX}-ioncube_loader-${PHP_EXTENSION_VERSION.${MODNAME}}
DISTNAME=		ioncube_loaders_${OS}_${SYSARCH}_${PHP_EXTENSION_VERSION.${MODNAME}}
MODNAME=		ioncube_loader
VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		devel
MASTER_SITES=		http://downloads3.ioncube.com/loader_downloads/
EXTRACT_SUFX=		.tar.gz

.include "../../mk/bsd.prefs.mk"
.if ${ABI} == 64
  SYSARCH=	x86-64
.else
  SYSARCH=	x86
.endif
.if ${OPSYS} == Linux
  OS=		lin
.elif ${OPSYS} == SunOS
  OS=		sun
.else
PKG_SKIP_REASON+=	"Operating system not supported"
.endif


MAINTAINER=		filip@joyent.com
COMMENT=		PHP ionCube Encoder

PKG_DESTDIR_SUPPORT=	user-destdir

NO_CHECKSUM=		yes
NO_BUILD=		yes
NO_CONFIGURE=		yes
EXTRACT_ELEMENTS=	# empty
WRKSRC=			${WRKDIR}/ioncube
MODULESDIR=		${WRKSRC}
INSTALLATION_DIRS+=	share/examples/ioncube
PLIST_SRC=		${.CURDIR}/PLIST

post-patch:
	cp -r ${WRKSRC}/ioncube_loader_${OS}_${PKG_PHP_VERSION:C/([0-9])([0-9])/\1.\2/}.so  \
		${WRKSRC}/${MODNAME}.so

.include "../../base/php/extension_versions.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
