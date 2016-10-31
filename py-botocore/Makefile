# $NetBSD: Makefile,v 1.12 2012/10/25 06:56:52 asau Exp $
#

DISTNAME=		botocore-${VERSION}
VERSION=		1.4.60
PKGNAME=		${PYPKGPREFIX}-${DISTNAME}
CATEGORIES=		textproc python
MASTER_SITES=		https://pypi.python.org/packages/11/3f/12932d40897c288c4138ac57898cbe751f2ee5930c91f670314b577b6438/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://github.com/boto/botocore
COMMENT=		A low-level interface to a growing number of Amazon Web Services. The botocore package is the foundation for the AWS CLI as well as boto3.
LICENSE=		Apache License 2.0

DEPENDS+=         ${PYPKGPREFIX}-tox>=2.1.1:../../devel/py-tox
DEPENDS+=         ${PYPKGPREFIX}-docutils>=0.12:../../textproc/py-docutils
DEPENDS+=         ${PYPKGPREFIX}-six>=1.10.0:../../lang/py-six
DEPENDS+=         ${PYPKGPREFIX}-dateutil>=2.4.0:../../time/py-dateutil
DEPENDS+=         ${PYPKGPREFIX}-nose>=1.3.7:../../devel/py-nose
DEPENDS+=         ${PYPKGPREFIX}-mock>=2.0.0:../../devel/py-mock
DEPENDS+=         ${PYPKGPREFIX}-wheel>=0.26.0:../../devel/py-wheel
DEPENDS+=         ${PYPKGPREFIX}-cElementTree>=${PY_DISTVERSION}:../../textproc/py-cElementTree
DEPENDS+=         ${PYPKGPREFIX}-jmespath>=0.9.0:../../base/py-jmespath
DEPENDS+=         ${PYPKGPREFIX}-behave>=1.2.5:../../base/py-behave

.include "../../lang/python/egg.mk"
_PYSETUPTOOLSINSTALLARGS= #nothing
.include "../../mk/bsd.pkg.mk"
