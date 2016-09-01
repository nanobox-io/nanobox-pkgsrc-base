# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		corosync-${VERSION}
VERSION=		2.3.5
PKGNAME=		corosync-${VERSION}
# PKGREVISION=		1
CATEGORIES=		base
MASTER_SITES=		https://github.com/ClusterLabs/corosync

MAINTAINER=		braxton@pagodabox.com
HOMEPAGE=		https://github.com/ClusterLabs/corosync
COMMENT=		Erlang is a programming language
LICENSE=		BSD

USE_LANGUAGES+=		c c++
_TOOLS_USE_PKGSRC.groff= yes
USE_TOOLS+=		gmake groff aclocal autoconf automake pkg-config gsed libtool

GNU_CONFIGURE=		yes
CONFIG_SHELL=		bash

GIT_REPOSITORIES=	corosync-${VERSION}
GIT_REPO.corosync-${VERSION}=	git@github.com:ClusterLabs/corosync.git
GIT_TAG=		v${VERSION}

pre-configure:
	which groff; \
	cd ${WRKSRC}; \
	./autogen.sh

BUILD_DEPENDS+=         groff>=1.22.3:../../textproc/groff
BUILD_DEPENDS+=         libtool-base>=2.4.2:../../devel/libtool-base

.include "../../devel/nss/buildlink3.mk"
.include "../../base/libqb/buildlink3.mk"
.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"
