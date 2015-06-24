# $NetBSD: Makefile,v 1.1 2015/01/14 21:01:19 adam Exp $

PKGNAME=	${DISTNAME:C/-/94-monitoring-/}
COMMENT=	PostgreSQL monitoring tools

DEPENDS+=	postgresql94-server>=${PKGVERSION_NOREV}:../../base/postgresql94-server

.include "../../base/postgresql94/Makefile.common"

BUILD_MAKE_FLAGS=	USE_PGXS=1

BUILD_DIRS+=		contrib/auto_explain
BUILD_DIRS+=		contrib/pg_buffercache
BUILD_DIRS+=		contrib/pg_stat_statements
BUILD_DIRS+=		contrib/pg_test_timing
BUILD_DIRS+=		contrib/pgstattuple

.include "../../base/postgresql94-client/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
