# $NetBSD: Makefile,v 1.1 2015/01/14 21:01:19 adam Exp $

PKGNAME=	${DISTNAME:C/-/94-pltcl-/}
COMMENT=	PL/Tcl procedural language for the PostgreSQL backend

DEPENDS+=	postgresql94-server>=${PKGVERSION_NOREV}:../../base/postgresql94-server

.include "../../base/postgresql94/Makefile.common"

CONFIGURE_ARGS+=	--with-tcl
CONFIGURE_ARGS+=	--with-tclconfig="${BUILDLINK_PREFIX.tcl}/lib"
CONFIGURE_ENV+=		TCLSH="${TCLSH}"
TCLSH=			${BUILDLINK_PREFIX.tcl}/bin/tclsh
BUILD_MAKE_FLAGS=	PGXS=1

BUILD_DIRS=		src/pl/tcl

.include "../../base/postgresql94-client/buildlink3.mk"
.include "../../lang/tcl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
