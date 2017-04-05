VERSION=	1.23
DISTNAME=	repo
PKGNAME=	repo-${VERSION}
CATEGORIES=	devel
MASTER_SITES=	https://storage.googleapis.com/git-repo-downloads/
EXTRACT_SUFX=	# none

MAINTAINER=	braxton@pagodabox.com
HOMEPAGE=	https://source.android.com/source/downloading.html
COMMENT=	Tool for downloading android
LICENSE=	# unknown

NO_BUILD=	yes
NO_CONFIGURE=	yes

do-extract:
	mkdir ${WRKSRC}
	cd ${WRKSRC} && cp ${DISTDIR}/${DISTFILES} .
	cd ${WRKSRC} && chmod 755 repo

do-install:
	mkdir ${DESTDIR}${PREFIX}/bin
	cd ${WRKSRC} && cp repo ${DESTDIR}${PREFIX}/bin

.include "../../lang/python/pyversion.mk"

DEPENDS+=	git-base>=1.6.4:../../devel/git-base
DEPENDS+=	${PYPKGPREFIX}-expat>=${PY_DISTVERSION}:../../textproc/py-expat

.include "../../lang/python27/buildlink3.mk"
.include "../../textproc/py-xml/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
