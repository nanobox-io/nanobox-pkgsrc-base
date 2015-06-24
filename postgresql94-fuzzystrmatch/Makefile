# $NetBSD: Makefile,v 1.1 2015/01/14 21:01:19 adam Exp $

PKGNAME=	${DISTNAME:C/-/94-fuzzystrmatch-/}
COMMENT=	PostgreSQL fuzzystrmatch contribution

DEPENDS+=	postgresql94-server>=${PKGVERSION_NOREV}:../../base/postgresql94-server

.include "../../base/postgresql94/Makefile.common"

BUILD_MAKE_FLAGS=	USE_PGXS=1

BUILD_DIRS=		contrib/fuzzystrmatch

.include "../../base/postgresql94-client/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
