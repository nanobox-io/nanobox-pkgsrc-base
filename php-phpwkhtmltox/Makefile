# $NetBSD: Makefile,v 1.18 2012/10/25 06:56:46 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		phpwkhtmltox
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES+=		textproc
COMMENT=		PHP extension for wkhtmltox support

CONFLICTS=		php-wkhtmltox-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}=shared,${BUILDLINK_DIR}

GIT_REPOSITORIES=	php-wkhtmltox
GIT_REPO.php-wkhtmltox=	git@github.com:mreiferson/php-wkhtmltox.git
GIT_BRANCH.php-wkhtmltox=	master

CPPFLAGS+=  		-I${WRKDIR}/${DISTNAME}

# USE_PHP_EXT_PATCHES=	# defined

# DEPENDS+=	wkhtmltopdf>=0.12.1:../../wip/wkhtmltopdf
# BUILDLINK_API_DEPENDS.wkhtmltopdf+= wkhtmltopdf-0.12.1
# BUILDLINK_ABI_DEPENDS.wkhtmltopdf+= wkhtmltopdf>=0.12.1

BUILDLINK_TREE+=  wkhtmltopdf

BUILDLINK_API_DEPENDS.wkhtmltopdf+= wkhtmltopdf-0.12.*
BUILDLINK_ABI_DEPENDS.wkhtmltopdf+= wkhtmltopdf>=0.12.1
BUILDLINK_PKGSRCDIR.wkhtmltopdf?= ../../base/wkhtmltopdf

BUILDLINK_TREE+=  -wkhtmltopdf

WRKSRC=		${WRKDIR}/php-wkhtmltox

.include "../../base/php/extension_versions.mk"
.include "../../base/php/ext.mk"
.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"
