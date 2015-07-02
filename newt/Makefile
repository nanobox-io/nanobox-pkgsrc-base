# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
#  # vim: ts=8 sw=8 ft=make noet


DISTNAME=		newt-${VERSION}
VERSION=		0.52.18
CATEGORIES=		pagoda
MASTER_SITES=		https://fedorahosted.org/releases/n/e/newt/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://fedorahosted.org/releases/n/e/newt/
COMMENT=		TODO: Short description of the package
#LICENSE=		# TODO: (see mk/license.mk)

INSTALLATION_DIRS=	bin lib include share/locale man

GNU_CONFIGURE=		yes
USE_TOOLS+=		pkg-config
USE_PKGLOCALEDIR=	yes
LDFLAGS+= -lintl

PKGCONFIG_OVERRIDE+=	libnewt.pc.in

USE_TOOLS+=gmake

SUBST_CLASSES+=		paths
SUBST_STAGE.paths=	pre-configure
SUBST_FILES.paths=	configure po/Makefile
SUBST_SED.paths=	-e "s|@PREFIX@|${PREFIX}|g"
SUBST_MESSAGE.paths=	Fixing paths.

.include "../../textproc/icu/buildlink3.mk"
.include "../../lang/tcl/buildlink3.mk"
.include "../../devel/libslang2/buildlink3.mk"
.include "../../devel/popt/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
