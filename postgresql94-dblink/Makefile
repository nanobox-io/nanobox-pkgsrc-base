# $NetBSD: Makefile,v 1.1 2015/01/14 21:01:19 adam Exp $

PKGNAME=	${DISTNAME:C/-/94-dblink-/}
COMMENT=	Dblink module for remote database connections

DEPENDS+=	postgresql94-server>=${PKGVERSION_NOREV}:../../base/postgresql94-server

.include "../../base/postgresql94/Makefile.common"

CONFIGURE_ARGS+=	--with-openssl
BUILD_MAKE_FLAGS=	USE_PGXS=1

BUILD_DIRS=		contrib/dblink

.include "../../base/postgresql94-client/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
