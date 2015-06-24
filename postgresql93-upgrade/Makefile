# $NetBSD: Makefile,v 1.3 2014/02/23 11:25:54 adam Exp $

PKGNAME=	${DISTNAME:C/-/93-upgrade-/}
COMMENT=	PostgreSQL binary upgrade tool
MAINTAINER=	pkgsrc-users@NetBSD.org

DEPENDS+=	postgresql93-server>=${PKGVERSION_NOREV}:../../base/postgresql93-server

.include "../../base/postgresql93/Makefile.common"

BUILD_MAKE_FLAGS=	PGXS=1

BUILD_DIRS+=		contrib/pg_upgrade
BUILD_DIRS+=		contrib/pg_upgrade_support

LIBS.SunOS+=	-lintl

.include "../../base/postgresql93-client/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
