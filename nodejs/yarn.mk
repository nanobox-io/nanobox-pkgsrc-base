# $NetBSD: Makefile.common,v 1.34.2.1 2014/04/14 15:29:21 tron Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
#  # vim: ts=8 sw=8 ft=make noet

.if !defined(YARN_MK)
YARN_MK=	# defined

YARN_VERSION=	1.5.1

YARN_DISTFILE=	yarn-v${YARN_VERSION}.tar.gz

YARN_SRC_DIR=		${WRKDIR}/yarn-v${YARN_VERSION}/
YARN_INSTALL_DIR=	${WRKSRC}/deps/yarn/

DISTFILES+=	${YARN_DISTFILE}

SITES.${YARN_DISTFILE}=	https://github.com/yarnpkg/yarn/releases/download/v${YARN_VERSION}/

.PHONY: yarn-install

yarn-install:
	mkdir -p ${YARN_INSTALL_DIR}
	cp -R ${YARN_SRC_DIR}* ${YARN_INSTALL_DIR}

.endif #YARN_MK
