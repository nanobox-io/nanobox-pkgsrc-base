# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
#  # vim: ts=8 sw=8 ft=make noet

VERSION=		2.2.11
DISTNAME=		sphinx-${VERSION}-release

PKGNAME=		${DISTNAME:S/-/search-client-/:S/-release//}
CATEGORIES=		databases textproc
MASTER_SITES=		http://www.sphinxsearch.com/files/

MAINTAINER=		filip@joyent.com
HOMEPAGE=		http://www.sphinxsearch.com/
COMMENT=		Sphinx Full-Text Search Engine
LICENSE=		gnu-gpl-v2

GNU_CONFIGURE=		yes
USE_LANGUAGES=		c c++
USE_LIBTOOL=		yes
BUILD_DEFS+=		VARBASE

.include "../../mk/bsd.prefs.mk"

WRKSRC=		${WRKDIR}/sphinx-${VERSION}-release/api/libsphinxclient

CONFIGURE_ARGS+= 	--enable-shared

.include "options.mk"

MAKE_JOBS_SAFE=		no
LDFLAGS.SunOS+=		-lsocket -lnsl

.include "../../textproc/expat/buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
