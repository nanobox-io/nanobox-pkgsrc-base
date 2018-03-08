# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		erlang-${VERSION}
VERSION=		19.3.6.6
PKGNAME=		erlang-${VERSION}
# PKGREVISION=		1
CATEGORIES=		base
MASTER_SITES=		http://www.erlang.org/download/

MAINTAINER=		braxton@pagodabox.com
HOMEPAGE=		http://www.erlang.org
COMMENT=		Erlang is a programming language
#LICENSE=		# TODO: (see mk/license.mk)

USE_LANGUAGES+=		c c++
USE_TOOLS+=		gmake perl aclocal autoconf automake
USE_JAVA=		yes
USE_JAVA2=		yes

HAS_CONFIGURE=		yes
# CONFIGURE_SCRIPT=	./otp_build configure

GIT_REPOSITORIES=	erlang-${VERSION}
GIT_REPO.erlang-${VERSION}=	git@github.com:erlang/otp.git
GIT_TAG.erlang-${VERSION}=	OTP-${VERSION}

# MAKE_JOBS_SAFE=		no

CONFIGURE_ARGS+=	--prefix=${PREFIX}

CONFIGURE_ARGS+=	--with-ssl=${BUILDLINK_PREFIX.openssl}

PTHREAD_OPTS+=		require native
CONFIGURE_ARGS+=	--enable-threads
CONFIGURE_ARGS+=	--enable-smp-support
CONFIGURE_ARGS+=	--enable-kernel-poll
CONFIGURE_ARGS+=	--enable-sctp
CONFIGURE_ARGS+=	--enable-hipe
CONFIGURE_ARGS+=	--with-odbc=${BUILDLINK_PREFIX.iodbc}
CONFIGURE_ARGS+=	--with-odbc=${BUILDLINK_PREFIX.unixodbc}
# CONFIGURE_ARGS+=	--with-dynamic-trace=systemtap
# CONFIGURE_ARGS+=	--enable-vm-probes

pre-configure:
	cd ${WRKSRC}; ./otp_build autoconf

.include "../../base/erlang19/versions.mk"


BUILD_DEPENDS+=         libxslt>=1.1.28:../../textproc/libxslt
BUILD_DEPENDS+=         fop>=1.1:../../textproc/fop
# BUILD_DEPENDS+=         wxGTK30>=3.0.2:../../x11/wxGTK30

.include "../../databases/unixodbc/buildlink3.mk"
.include "../../databases/iodbc/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../devel/ncurses/buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../base/java/java-vm.mk"
.include "../../mk/termcap.buildlink3.mk"
.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"
