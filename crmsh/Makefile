# $NetBSD: Makefile,v 1.27 2015/12/05 21:25:47 adam Exp $

DISTNAME=	crmsh-${VERSION}
VERSION=	2.3.1
CATEGORIES=	base
MASTER_SITES=	https://github.com/ClusterLabs/crmsh

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/ClusterLabs/crmsh
COMMENT=	crmsh is a cluster management shell for the Pacemaker High Availability stack.
LICENSE=	GPL-2

USE_TOOLS+=		gmake aclocal autoconf automake pkg-config

GNU_CONFIGURE=		yes
CONFIG_SHELL=		bash

GIT_REPOSITORIES=	crmsh-${VERSION}
GIT_REPO.crmsh-${VERSION}=	git@github.com:ClusterLabs/crmsh.git
GIT_TAG=		${VERSION}

pre-configure:
	cd ${WRKSRC}; \
	./autogen.sh

DEPENDS+=         ${PYPKGPREFIX}-lxml>=3.5.0:../../textproc/py-lxml
DEPENDS+=         ${PYPKGPREFIX}-readline>=${PY_DISTVERSION}:../../devel/py-readline
DEPENDS+=         ${PYPKGPREFIX}-curses>=${PY_DISTVERSION}:../../devel/py-curses
DEPENDS+=         ${PYPKGPREFIX}-dateutil>=2.4.0:../../time/py-dateutil
DEPENDS+=         ${PYPKGPREFIX}-yaml>=3.11:../../textproc/py-yaml

DEPENDS+=         ${PYPKGPREFIX}-nosexcover>=1.0.10:../../base/py-nosexcover
DEPENDS+=         ${PYPKGPREFIX}-parallax>=1.0.1:../../base/py-parallax

.include "../../base/python/egg.mk"
.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"
