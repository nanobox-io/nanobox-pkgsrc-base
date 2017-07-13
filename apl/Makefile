# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

PKGNAME=		apl-${VERSION}
VERSION=		1.7
# PKGREVISION=		1
CATEGORIES=		www
DISTNAME=		apl-${VERSION}
MASTER_SITES=		${MASTER_SITE_GNU:=apl/}

HOMEPAGE=		https://www.gnu.org/software/apl/
COMMENT=		GNU APL is a free interpreter for the programming language APL. 
LICENSE=		gnu-gpl-v3

USE_LANGUAGES=		c c++

CONFIG_SHELL=		/bin/bash
GNU_CONFIGURE=		yes

BUILD_DEPENDS+=		subversion-base>=1.9.5:../../devel/subversion-base

SVN_REPOSITORIES=	apl
SVN_REPO.apl=		http://svn.savannah.gnu.org/svn/apl
SVN_BRANCH.apl=		trunk	

WRKSRC=			${WRKDIR}/apl

.include "../../base/subversion/svn-package.mk"
.include "../../mk/bsd.prefs.mk"
.include "../../mk/bsd.pkg.mk"
