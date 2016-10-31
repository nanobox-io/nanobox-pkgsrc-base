# $NetBSD: Makefile,v 1.12 2012/10/25 06:56:52 asau Exp $
#

DISTNAME=		s3transfer-${VERSION}
VERSION=		0.1.7
PKGNAME=		${PYPKGPREFIX}-${DISTNAME}
CATEGORIES=		textproc python
MASTER_SITES=		https://pypi.python.org/packages/e9/a5/c69e87e716c5ec1fb2c44db87dab969f86a9f122cfc8f986995a4d59c191/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://github.com/boto/s3transfer
COMMENT=		An Amazon S3 Transfer Manager
LICENSE=		Apache

DEPENDS+=         ${PYPKGPREFIX}-botocore>=1.4.60:../../base/py-botocore
DEPENDS+=         ${PYPKGPREFIX}-futures>=3.0.5:../../devel/py-futures

.include "../../lang/python/egg.mk"
.include "../../mk/bsd.pkg.mk"
