# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

VERSION=        	1
DISTNAME=       	librpcsoc-${VERSION}
CATEGORIES=     	pagoda
MASTER_SITES=   	http://bitbucket.org/pagodaboxgrid/librpcsoc

MAINTAINER=     	pkgsrc-users@NetBSD.org
HOMEPAGE=       	http://bitbucket.org/pagodaboxgrid/librpcsoc
COMMENT=        	librpcsoc from the ucblibs
#LICENSE=       	# TODO: (see mk/license.mk)

USE_TOOLS+= 		aclocal autoconf automake
GNU_CONFIGURE=  	yes

WRKSRC=			${WRKDIR}/librpcsoc

GIT_REPOSITORIES=	librpcsoc
GIT_REPO.librpcsoc=	braxton@172.16.35.1:/Users/braxton/src/pagodaboxshovel/librpcsoc/.git
GIT_BRANCH.librpcsoc=	master

CFLAGS+= 		-g
CONFIGURE_ARGS+= 	--prefix=/opt/local

pre-configure:
	cd $(WRKSRC) && autoreconf -vfi

.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"
