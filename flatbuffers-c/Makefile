# $NetBSD: Makefile.common,v 1.34.2.1 2014/04/14 15:29:21 tron Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
#  # vim: ts=8 sw=8 ft=make noet

PKGNAME=	flatbuffers-c-${VERSION}
VERSION=	1.6.0
CATEGORIES=	net

MAINTAINER?=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/google/flatbuffers
LICENSE=	Apache-2.0

USE_CMAKE=		yes
USE_LANGUAGES=		c c++

GIT_REPOSITORIES=	flatbuffers
GIT_REPO.flatbuffers=	git@github.com:google/flatbuffers.git
GIT_TAG.flatbuffers=	v${VERSION}

WRKSRC=		${WRKDIR}/flatbuffers

.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"
