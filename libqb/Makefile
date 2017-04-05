# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		libqb-${VERSION}
VERSION=		1.0
PKGNAME=		libqb-${VERSION}
# PKGREVISION=		1
CATEGORIES=		base
MASTER_SITES=		https://github.com/ClusterLabs/libqb

MAINTAINER=		braxton@pagodabox.com
HOMEPAGE=		https://github.com/ClusterLabs/libqb
COMMENT=		Erlang is a programming language
LICENSE=		LGPL2.1

USE_LANGUAGES+=		c c++
USE_TOOLS+=		gmake aclocal autoconf automake pkg-config gsed libtool

GNU_CONFIGURE=		yes
CONFIG_SHELL=		bash

GIT_REPOSITORIES=	libqb-${VERSION}
GIT_REPO.libqb-${VERSION}=	git@github.com:ClusterLabs/libqb.git
GIT_TAG.libqb-${VERSION}=	v${VERSION}

pre-configure:
	cd ${WRKSRC}; \
	./autogen.sh

BUILD_DEPENDS+=         libtool-base>=2.4.2:../../devel/libtool-base

.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"
