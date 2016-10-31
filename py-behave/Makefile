# $NetBSD: Makefile,v 1.12 2012/10/25 06:56:52 asau Exp $
#

DISTNAME=		behave-${VERSION}
VERSION=		1.2.5
PKGNAME=		${PYPKGPREFIX}-${DISTNAME}
CATEGORIES=		textproc python
MASTER_SITES=		https://pypi.python.org/packages/9e/fd/430a2784e4892b2585dd1926acd847b815e3fc0f00fbe0800e376b9c0222/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://github.com/behave/behave
COMMENT=		behave is behaviour-driven development, Python style
LICENSE=		bsd

DEPENDS+=		${PYPKGPREFIX}-argparse>=1.2.1:../../devel/py-argparse
DEPENDS+=               ${PYPKGPREFIX}-parse>=1.6.6:../../base/py-parse
DEPENDS+=               ${PYPKGPREFIX}-parse_type>=0.3.4:../../base/py-parse_type
DEPENDS+=		${PYPKGPREFIX}-six>=1.7:../../lang/py-six
DEPENDS+=               ${PYPKGPREFIX}-jsonschema>=2.4.0:../../textproc/py-jsonschema

.include "../../lang/python/egg.mk"
.include "../../mk/bsd.pkg.mk"
