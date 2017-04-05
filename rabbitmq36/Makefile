# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

VERSION=		3.6.6
DISTNAME=		rabbitmq-server-${VERSION}
PKGNAME=		${DISTNAME:S/-server//}
CATEGORIES=		pagoda
MASTER_SITES=	https://www.rabbitmq.com/releases/rabbitmq-server/v${VERSION}/
EXTRACT_SUFX=	.tar.xz

USE_TOOLS+=	bash:run gmake unzip zip

BUILD_DEPENDS+=		${PYPKGPREFIX}-expat-[0-9]*:../../textproc/py-expat
BUILD_DEPENDS+=		libxslt-[0-9]*:../../textproc/libxslt
BUILD_DEPENDS+=		rsync-[0-9]*:../../net/rsync
BUILD_DEPENDS+=		xmlto-[0-9]*:../../textproc/xmlto
DEPENDS+=		${PYPKGPREFIX}-simplejson>=2:../../converters/py-simplejson

INSTALL_TARGET=		install-erlapp install-scripts install-bin install-man

SCRIPTS_DIR=		${WRKSRC}/scripts

REPLACE_BASH+=		${SCRIPTS_DIR}/rabbitmqctl
REPLACE_BASH+=		${SCRIPTS_DIR}/rabbitmq-defaults
REPLACE_BASH+=		${SCRIPTS_DIR}/rabbitmq-env
REPLACE_BASH+=		${SCRIPTS_DIR}/rabbitmq-plugins
REPLACE_BASH+=		${SCRIPTS_DIR}/rabbitmq-server

MAKE_ENV+=		MANDIR="${PREFIX}/${PKGMANDIR}"
MAKE_ENV+=		RMQ_BINDIR="${PREFIX}/sbin"
MAKE_ENV+=		RMQ_LIBDIR="${PREFIX}/lib/erlang/lib"
MAKE_ENV+=		RSYNC="${PREFIX}/bin/rsync"

.include "../../base/erlang19/buildlink3.mk"
.include "../../lang/python/application.mk"
.include "../../mk/bsd.pkg.mk"
