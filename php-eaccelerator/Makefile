# $NetBSD: Makefile,v 1.20 2012/12/05 15:28:30 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		eaccelerator
PKGREVISION=		1
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		sysutils
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=eaccelerator/} \
			http://bart.eaccelerator.net/source/${PECL_VERSION}/
EXTRACT_SUFX=		.tar.bz2

HOMEPAGE=		https://github.com/eaccelerator/eaccelerator
MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		PHP accelerator, optimizer, encoder and dynamic content cache
LICENSE=		gnu-gpl-v2

PHP_VERSIONS_ACCEPTED=	53 54

CONFLICTS=		php-eaccelator-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}

GIT_REPOSITORIES=	eaccelerator
GIT_REPO.eaccelerator=	git@github.com:eaccelerator/eaccelerator.git
GIT_BRANCH.eaccelerator=	master

WRKSRC=			${WRKDIR}/eaccelerator

.include "options.mk"

.include "../../base/git/git-package.mk"
.include "../../base/php/extension_versions.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
