# $NetBSD: Makefile,v 1.12 2012/10/25 06:56:52 asau Exp $
#

DISTNAME=		parse_type-${VERSION}
VERSION=		0.3.4
PKGNAME=		${PYPKGPREFIX}-${DISTNAME}
CATEGORIES=		textproc python
MASTER_SITES=		https://pypi.python.org/packages/3e/d0/4edd333af8c085eb2420272e1dab2cfc643bac4767231c20d7f63c643822/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://github.com/jenisys/parse_type
COMMENT=		Simplifies to build parse types based on the parse module
LICENSE=		bsd

DEPENDS+=	${PYPKGPREFIX}-enum34>=1.1.6:../../devel/py-enum34
DEPENDS+=         ${PYPKGPREFIX}-six>=1.10.0:../../lang/py-six
DEPENDS+=         ${PYPKGPREFIX}-parse>=1.6.6:../../base/py-parse

.include "../../lang/python/egg.mk"
.include "../../mk/bsd.pkg.mk"
