# $NetBSD: Makefile,v 1.3 2016/04/09 12:51:50 adam Exp $

PKGNAME=	${DISTNAME:C/-/95-monitoring-/}
COMMENT=	PostgreSQL monitoring tools

DEPENDS+=	postgresql95-server>=${PKGVERSION_NOREV}:../../base/postgresql95-server

.include "../../base/postgresql95/Makefile.common"

BUILD_MAKE_FLAGS=	USE_PGXS=1

BUILD_DIRS+=		contrib/auto_explain
BUILD_DIRS+=		contrib/pg_buffercache
BUILD_DIRS+=		contrib/pg_stat_statements
BUILD_DIRS+=		contrib/pgstattuple

.include "../../base/postgresql95-client/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
