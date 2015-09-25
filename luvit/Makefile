# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

VERSION=		2.5.5
DISTNAME=		luvit-${VERSION}
# PKGREVISION=		
CATEGORIES=		pagoda
MASTER_SITES=		https://github.com/luvit/luvit

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://github.com/luvit/luvit
COMMENT= 		luvit framework
#LICENSE=		# TODO: (see mk/license.mk)
REPO=			git@github.com:luvit/luvit.git

USE_TOOLS+=		gmake
USE_LANGUAGES+=		c c++
ENVIRONMENT+=		PATH=/usr/local/sbin:/usr/local/bin:/opt/local/sbin:/opt/local/bin:/usr/sbin:/usr/bin:/sbin
ENVIRONMENT+=		LINK=g++

MAKE_ENV+=		PREFIX=${PREFIX}
MAKE_ENV+=		DESTDIR=${DESTDIR}

MAKE_JOBS_SAFE=		no

BUILD_TARGET=		luvit

do-wrapper:
	@${DO_NADA}

.PHONY: pre-fetch git-clone git-checkout git-submodule-update cache-git
.if exists(${DISTDIR}/${DISTFILES})
pre-fetch:
.else
pre-fetch: cache-git
.endif

git-clone: 
	if [ ! -d ${WRKSRC} ]; then \
		git clone --recursive ${REPO} ${WRKSRC}; \
	fi

git-checkout: git-clone
	cd ${WRKSRC}; git checkout ${VERSION}

git-submodule-update: git-checkout
	cd ${WRKSRC}; git submodule update --init --recursive

cache-git: git-submodule-update
	if [ ! -f ${DISTDIR}/${DISTFILES} ]; then \
		tar -czf ${DISTDIR}/${DISTFILES} -C ${WRKDIR} ${DISTNAME}; \
	fi

.include "../../mk/bsd.pkg.mk"