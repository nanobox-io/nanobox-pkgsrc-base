# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=	percona-xtrabackup-${VERSION}
VERSION=	2.2.12
CATEGORIES=	pagoda
MASTER_SITES=	http://www.percona.com/redir/downloads/XtraBackup/LATEST/source/tarball/

MAINTAINER=	braxton@pagodabox.com
HOMEPAGE=	http://galeracluster.com/
COMMENT=	XtraBackup by Percona
# LICENSE=	modified-bsd

BUILD_DEPENDS+=	py27-sphinx>=1.2:../../textproc/py-sphinx

USE_CMAKE=	yes
USE_LANGUAGES=	c c++
USE_TOOLS=	cmake automake autoconf bison libtool perl

# CFLAGS+=	-D_POSIX_PTHREAD_SEMANTICS
CMAKE_ARGS+=	-DENABLE_DTRACE=OFF
CMAKE_ARGS+=	-DBUILD_CONFIG=xtrabackup_release

.include "../../mk/bsd.prefs.mk"
.include "../../base/libaio/buildlink3.mk"
.include "../../base/libacl/buildlink3.mk"
.include "../../archivers/bzip2/buildlink3.mk"
.include "../../archivers/xz/buildlink3.mk"
.include "../../security/libgcrypt/buildlink3.mk"
.include "../../security/libgpg-error/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
