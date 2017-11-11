# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		lttng-ust-${VERSION}
VERSION=		2.10.0
PKGNAME=		lttng-ust-${VERSION}
# PKGREVISION=		1
CATEGORIES=		devel
DISTFILES=		lttng-ust-2.10.0.tar.bz2

SITES.lttng-ust-${VERSION}.tar.bz2=	http://lttng.org/files/lttng-ust/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://lttng.org/
COMMENT=		Linux Trace Toolkit: next generation
LICENSE=		mit gnu-lgpl-v2.1 gnu-gpl-v2

USE_TOOLS+=		gmake

USE_LANGUAGES+=		c c++

GNU_CONFIGURE=          yes

.include "../../devel/userspace-rcu/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
