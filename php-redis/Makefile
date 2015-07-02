# $NetBSD: Makefile,v 1.4 2012/10/02 21:25:40 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
#

MODNAME=		redis
PECL_VERSION=		${PHP_EXTENSION_VERSION.${MODNAME}}
PECL_DISTNAME=		phpredis-${PECL_VERSION}
DISTNAME=		phpredis
CATEGORIES=		databases
MASTER_SITES=		http://download.github.com/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://github.com/nicolasff/phpredis
COMMENT=		PHP extension for Redis
LICENSE=		php

GIT_REPOSITORIES=	php-redis
GIT_REPO.php-redis=	git://github.com/nicolasff/phpredis.git
GIT_TAG=		${PECL_VERSION}

WRKSRC=			${WRKDIR}/php-redis

.include "../../base/php/extension_versions.mk"
.include "../../base/git/git-package.mk"
.include "../../base/php-session/buildlink3.mk"
.include "../../base/php-igbinary/buildlink3.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
