# $NetBSD: Makefile,v 1.12 2012/10/25 06:56:52 asau Exp $
#

DISTNAME=		parallax-${VERSION}
VERSION=		1.0.1
PKGNAME=		${PYPKGPREFIX}-${DISTNAME}
CATEGORIES=		textproc python
MASTER_SITES=		https://pypi.python.org/packages/a8/14/52445e28ad7c9945dcf19d5ee86972aa0dac91d70f5dddbf38f8489b0eed/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://github.com/krig/parallax/
COMMENT=		Execute commands and copy files over SSH to multiple machines at once
LICENSE=		bsd

.include "../../lang/python/egg.mk"
_PYSETUPTOOLSINSTALLARGS= #nothing
.include "../../mk/bsd.pkg.mk"
