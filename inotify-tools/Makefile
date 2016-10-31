# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		inotify-tools-${VERSION}
VERSION=		3.14
#PKGREVISION=		1
CATEGORIES=		net
MASTER_SITES=		https://github.com/rvoicilas/inotify-tools

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://github.com/rvoicilas/inotify-tools
COMMENT=		inotify-tools
LICENSE=		GPL2

GNU_CONFIGURE=		yes
USE_TOOLS+=		aclocal autoconf automake libtool

BUILD_DEPENDS+=         libtool-base>=2.4.2:../../devel/libtool-base

.include "../../mk/bsd.prefs.mk"

GIT_REPOSITORIES=       inotify-tools
GIT_REPO.inotify-tools=	git@github.com:rvoicilas/inotify-tools.git
GIT_TAG=                v${VERSION}

WRKSRC=			${WRKDIR}/inotify-tools

pre-configure:
	cd ${WRKSRC} && autoreconf -vfi

.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"
