# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		r${VERSION}
VERSION?=		3.4.13
PKGNAME=		mongodb34-tools-${VERSION}
# PKGREVISION?=		1
CATEGORIES=		databases
MASTER_SITES=		https://github.com/mongodb/mongo-tools/archive/

#https://github.com/mongodb/mongo-tools/archive/r3.0.4.zip

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		github.com/mongodb/mongo-tools
COMMENT=		Tools for managing mongodb
#LICENSE=       	# TODO: (see mk/license.mk)

WRKSRC=			${WRKDIR}/mongo-tools-r${VERSION}

USE_LANGUAGES+=		c

USE_TOOLS+=		gsed

GO_DOMAIN=		github.com
GO_USER=		mongodb
GO_PROJECT=		mongo-tools

do-build:
	@cd ${WRKSRC}; CGO_LDFLAGS="${LDFLAGS}" ./build.sh

do-install:
	@mkdir -p ${DESTDIR}${PREFIX}
	@cp -r ${WRKSRC}/bin ${DESTDIR}${PREFIX}

# .include "../../base/git/git-package.mk"
.include "../../base/go/go-app.mk"
.include "../../net/libpcap/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"

