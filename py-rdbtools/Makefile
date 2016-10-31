# $NetBSD: Makefile,v 1.12 2012/10/25 06:56:52 asau Exp $
#

DISTNAME=		rdbtools-${VERSION}
VERSION=		0.1.7
PKGNAME=		${PYPKGPREFIX}-${DISTNAME}
CATEGORIES=		textproc python
MASTER_SITES=		https://github.com/sripathikrishnan/redis-rdb-tools/archive/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://github.com/sripathikrishnan/redis-rdb-tools
COMMENT=		Utilities to convert Redis RDB files to JSON or SQL formats
LICENSE=		mit

WRKSRC=			${WRKDIR}/redis-rdb-tools-rdbtools-${VERSION}

.include "../../lang/python/egg.mk"
#_PYSETUPTOOLSINSTALLARGS= #nothing
.include "../../mk/bsd.pkg.mk"
