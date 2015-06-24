# $NetBSD: Makefile,v 1.3 2014/02/23 11:25:54 adam Exp $

PKGNAME=	${DISTNAME:C/-/93-dblink-/}
COMMENT=	Dblink module for remote database connections

DEPENDS+=	postgresql93-server>=${PKGVERSION_NOREV}:../../base/postgresql93-server

.include "../../base/postgresql93/Makefile.common"

CONFIGURE_ARGS+=	--with-openssl
BUILD_MAKE_FLAGS=	PGXS=1

BUILD_DIRS=		contrib/dblink

.include "../../base/postgresql93-client/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
