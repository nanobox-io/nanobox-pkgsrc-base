# $NetBSD: Makefile,v 1.12 2012/10/25 06:56:52 asau Exp $
#

DISTNAME=		rethinkdb-${VERSION}
VERSION=		2.3.0
PKGNAME=		${PYPKGPREFIX}-${DISTNAME}
CATEGORIES=		textproc python
MASTER_SITES=		https://pypi.python.org/packages/4c/a8/384144095230d21928c7d9615acb111c6ed4cd2af1aef5e8fe9d528451c0/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://github.com/sripathikrishnan/redis-rdb-tools
COMMENT=		Utilities to convert Redis RDB files to JSON or SQL formats
LICENSE=		mit

#WRKSRC=			${WRKDIR}/redis-rdb-tools-rdbtools-${VERSION}

.include "../../lang/python/egg.mk"
#_PYSETUPTOOLSINSTALLARGS= #nothing
.include "../../mk/bsd.pkg.mk"
