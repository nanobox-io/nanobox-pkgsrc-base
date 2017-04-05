# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

VERSION=		0.2.0
DISTNAME=		flip-${VERSION}
# PKGREVISION=		
CATEGORIES=		pagoda
MASTER_SITES=		https://github.com/fliping/flip

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://github.com/fliping/flip
COMMENT= 		Flip manages flipping data between nodes in a cluster
LICENSE=		MIT

GIT_REPOSITORIES=	flip
GIT_REPO.flip=		git@github.com:fliping/flip.git
GIT_TAG.flip=		v${VERSION}

WRKSRC=			${WRKDIR}/flip

.include "../../base/git/git-package.mk"
.include "../../base/luvit/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
