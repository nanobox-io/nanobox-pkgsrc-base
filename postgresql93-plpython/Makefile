# $NetBSD: Makefile,v 1.5 2014/07/25 22:14:57 adam Exp $

PKGNAME=	${DISTNAME:C/-/93-plpython-/}
COMMENT=	PL/Python procedural language for the PostgreSQL backend

DEPENDS+=	postgresql93-server>=${PKGVERSION_NOREV}:../../base/postgresql93-server

.include "../../base/postgresql93/Makefile.common"

CONFIGURE_ARGS+=	--with-python
CONFIGURE_ENV+=		PYTHON="${PYTHONBIN}"
BUILD_MAKE_FLAGS=	PGXS=1

BUILD_DIRS=		src/pl/plpython

.include "../../base/postgresql93-client/buildlink3.mk"
.include "../../lang/python/extension.mk"
.include "../../mk/bsd.pkg.mk"
