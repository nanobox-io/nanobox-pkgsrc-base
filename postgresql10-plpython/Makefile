# $NetBSD: Makefile,v 1.1 2017/10/23 20:33:49 adam Exp $

PKGNAME=	${DISTNAME:C/-/10-plpython-/}
COMMENT=	PL/Python procedural language for the PostgreSQL backend
PKGREVISION=	1

DEPENDS+=	postgresql10-server>=${PKGVERSION_NOREV}:../../base/postgresql10-server

.include "../../base/postgresql10/Makefile.common"

CONFIGURE_ARGS+=	--with-python
CONFIGURE_ENV+=		PYTHON="${PYTHONBIN}"
BUILD_MAKE_FLAGS=	PGXS=1

BUILD_DIRS=		src/pl/plpython contrib/hstore_plpython

.include "../../base/postgresql10-client/buildlink3.mk"
.include "../../lang/python/extension.mk"
.include "../../mk/bsd.pkg.mk"
