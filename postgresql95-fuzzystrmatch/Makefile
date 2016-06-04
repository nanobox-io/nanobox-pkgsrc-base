# $NetBSD: Makefile,v 1.3 2016/04/09 12:51:50 adam Exp $

PKGNAME=	${DISTNAME:C/-/95-fuzzystrmatch-/}
COMMENT=	PostgreSQL fuzzystrmatch contribution

DEPENDS+=	postgresql95-server>=${PKGVERSION_NOREV}:../../base/postgresql95-server

.include "../../base/postgresql95/Makefile.common"

BUILD_MAKE_FLAGS=	USE_PGXS=1

BUILD_DIRS=		contrib/fuzzystrmatch

.include "../../base/postgresql95-client/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
