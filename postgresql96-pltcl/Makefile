# $NetBSD: Makefile,v 1.1 2016/10/29 19:41:55 adam Exp $

PKGNAME=	${DISTNAME:C/-/96-pltcl-/}
COMMENT=	PL/Tcl procedural language for the PostgreSQL backend

DEPENDS+=	postgresql96-server>=${PKGVERSION_NOREV}:../../base/postgresql96-server

.include "../../base/postgresql96/Makefile.common"

CONFIGURE_ARGS+=	--with-tcl
CONFIGURE_ARGS+=	--with-tclconfig="${BUILDLINK_PREFIX.tcl}/lib"
CONFIGURE_ENV+=		TCLSH="${TCLSH}"
TCLSH=			${BUILDLINK_PREFIX.tcl}/bin/tclsh
BUILD_MAKE_FLAGS=	PGXS=1

BUILD_DIRS=		src/pl/tcl

.include "../../base/postgresql96-client/buildlink3.mk"
.include "../../lang/tcl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
