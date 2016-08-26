# $NetBSD: Makefile,v 1.2 2012/10/23 17:18:58 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
#

MODNAME=				amqp
PECL_VERSION=				${PHP_EXTENSION_VERSION.${MODNAME}}
CATEGORIES=				net

MAINTAINER=				pkgsrc-users@NetBSD.org
HOMEPAGE=				http://pecl.php.net/package/${MODNAME}/
COMMENT=				PHP module to connect to AMQP services
LICENSE=				php

CONFIGURE_ARGS+=			--with-${MODNAME}
CONFIGURE_ARGS+=			--with-${PKGMODNAME}=shared,${BUILDLINK_DIR}
CONFIGURE_ARGS+=			--with-librabbitmq-dir=${PREFIX}

BUILDLINK_TREE+=			rabbitmq-c
RABBITMQ_C_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.rabbitmq-c+=	rabbitmq-c>=0.3.0
BUILDLINK_PKGSRCDIR.rabbitmq-c?=	../../net/rabbitmq-c

BUILDLINK_TREE+=			-rabbitmq-c

.include "../../base/php/extension_versions.mk"
.include "../../base/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
