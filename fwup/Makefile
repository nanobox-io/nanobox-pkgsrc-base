# $NetBSD: Makefile,v 1.2 2014/05/29 23:35:35 wiz Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

VERSION=	0.12.0
DISTNAME=	fwup-${VERSION}
# PKGREVISION=	1
CATEGORIES=	devel
MASTER_SITES=	https://github.com/fhunleth/fwup

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/fhunleth/fwup
COMMENT=	The fwup utility is a configurable image-based firmware update utility for embedded Linux-based systems.
LICENSE=	apache-2.0

GNU_CONFIGURE=	yes
USE_TOOLS+=		aclocal autoconf automake libtool pkg-config

BUILD_DEPENDS+=         libtool-base>=2.4.2:../../devel/libtool-base

GIT_REPOSITORIES=	fwup
GIT_REPO.fwup=		git@github.com:fhunleth/fwup.git
GIT_TAG.fwup=		v${VERSION}

WRKSRC=			${WRKDIR}/fwup

pre-configure:
	cd ${WRKSRC} && ./autogen.sh

.include "../../base/git/git-package.mk"
.include "../../archivers/libarchive/buildlink3.mk"
.include "../../devel/confuse/buildlink3.mk"
.include "../../security/libsodium/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
