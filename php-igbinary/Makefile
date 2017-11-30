# $NetBSD: Makefile,v 1.23 2013/03/17 10:46:45 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
	
MODNAME=		igbinary
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		devel

MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		igbinary extension
LICENSE=		php


CONFLICTS=		php-igbinary-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}
WRKSRC=			${WRKDIR}/igbinary-${PECL_VERSION}

PLIST_SRC+=		${.CURDIR}/PLIST.extras
PLIST_SUBST+=		PKGBASE=${PKGBASE:Q}

IGBINARY_INCLUDES=	igbinary.h

INSTALLATION_DIRS+=	include/php/ext/igbinary


.include "../../base/php/extension_versions.mk"

.if ${PKG_PHP_MAJOR_VERS} == "7"
# GIT_REPOSITORIES=	igbinary-${PECL_VERSION}
# GIT_REPO.igbinary-${PECL_VERSION}=	git://github.com/igbinary/igbinary.git
# GIT_BRANCH.igbinary-${PECL_VERSION}=		php7-dev-playground2
#
# .include "../../base/git/git-package.mk"
INCLUDE_DIR=	src/php7
.else
INCLUDE_DIR=	src/php5
.endif
post-install:
.for inc in ${IGBINARY_INCLUDES}
	${INSTALL_DATA} ${WRKSRC}/${INCLUDE_DIR}/${inc} ${DESTDIR}${PREFIX}/include/php/ext/igbinary/${inc}
.endfor

.include "../../base/php-session/buildlink3.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
