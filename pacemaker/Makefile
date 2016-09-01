# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		pacemaker-${VERSION}
VERSION=		1.1.15
PKGNAME=		pacemaker-${VERSION}
# PKGREVISION=		1
CATEGORIES=		base
MASTER_SITES=		https://github.com/ClusterLabs/pacemaker

MAINTAINER=		braxton@pagodabox.com
HOMEPAGE=		https://github.com/ClusterLabs/pacemaker
COMMENT=		Erlang is a programming language
LICENSE=		GPL2

USE_LANGUAGES+=		c
# _TOOLS_USE_PKGSRC.groff= yes
USE_TOOLS+=		gmake aclocal autoconf automake pkg-config gsed libtool

GNU_CONFIGURE=		yes
CONFIG_SHELL=		bash

GIT_REPOSITORIES=	pacemaker-${VERSION}
GIT_REPO.pacemaker-${VERSION}=	git@github.com:ClusterLabs/pacemaker.git
GIT_TAG=		Pacemaker-${VERSION}

pre-configure:
	cd ${WRKSRC}; \
	./autogen.sh

# .include "../../devel/nss/buildlink3.mk"
# .include "../../base/libqb/buildlink3.mk"
.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"
