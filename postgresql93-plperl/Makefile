# $NetBSD: Makefile,v 1.5 2014/07/25 22:14:57 adam Exp $

PKGNAME=	${DISTNAME:C/-/93-plperl-/}
COMMENT=	PL/Perl procedural language for the PostgreSQL backend

DEPENDS+=	postgresql93-server>=${PKGVERSION_NOREV}:../../base/postgresql93-server

.include "../../base/postgresql93/Makefile.common"

USE_TOOLS+=		perl
PERL5_CONFIGURE=	no
CONFIGURE_ARGS+=	--with-perl
BUILD_MAKE_FLAGS=	PGXS=1

BUILD_DIRS=		src/pl/plperl
MAKE_FILE=		GNUmakefile

.include "../../base/postgresql93-client/buildlink3.mk"
.include "../../lang/perl5/module.mk"
.include "../../mk/bsd.pkg.mk"
