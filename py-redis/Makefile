# $NetBSD: Makefile,v 1.12 2012/10/25 06:56:52 asau Exp $
#

DISTNAME=		redis-${VERSION}
VERSION=		2.10.5
PKGNAME=		${PYPKGPREFIX}-${DISTNAME}
CATEGORIES=		databases python
MASTER_SITES=		https://pypi.python.org/packages/68/44/5efe9e98ad83ef5b742ce62a15bea609ed5a0d1caf35b79257ddb324031a/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://pypi.python.org/pypi/redis	
COMMENT=		The Python interface to the Redis key-value store.
LICENSE=		mit

#WRKSRC=			${WRKDIR}/redis-rdb-tools-rdbtools-${VERSION}

.include "../../lang/python/egg.mk"
#_PYSETUPTOOLSINSTALLARGS= #nothing
.include "../../mk/bsd.pkg.mk"
