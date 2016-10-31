# $NetBSD: Makefile,v 1.12 2012/10/25 06:56:52 asau Exp $
#

DISTNAME=		awscli-${VERSION}
VERSION=		1.11.2
PKGREVISION=		1
PKGNAME=		${PYPKGPREFIX}-${DISTNAME}
CATEGORIES=		textproc python
MASTER_SITES=		https://pypi.python.org/packages/95/90/e2cf344edaad1bea9fce56920fed7c3dfa314ef23685218f19e4b9850561/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://aws.amazon.com/cli/
COMMENT=		This package provides a unified command line interface to Amazon Web Services.
LICENSE=		Apache License 2.0

DEPENDS+=         ${PYPKGPREFIX}-botocore>=1.4.60:../../base/py-botocore
DEPENDS+=         ${PYPKGPREFIX}-colorama>=0.3.2:../../comms/py-colorama
DEPENDS+=         ${PYPKGPREFIX}-docutils>=0.12:../../textproc/py-docutils
DEPENDS+=         ${PYPKGPREFIX}-rsa>=3.4.1:../../security/py-rsa
DEPENDS+=         ${PYPKGPREFIX}-s3transfer>=0.1.7:../../base/py-s3transfer
DEPENDS+=         ${PYPKGPREFIX}-nose>=1.3.7:../../devel/py-nose
DEPENDS+=         ${PYPKGPREFIX}-mock>=2.0.0:../../devel/py-mock
DEPENDS+=         ${PYPKGPREFIX}-wheel>=0.26.0:../../devel/py-wheel

.include "../../lang/python/egg.mk"
_PYSETUPTOOLSINSTALLARGS= #nothing
.include "../../mk/bsd.pkg.mk"
