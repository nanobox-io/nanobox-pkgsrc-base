DISTNAME=	couchbase-${VERSION}
PKGNAME=	couchbase-${VERSION}
VERSION=	4.6.0
CATEGORIES=	databases

USE_TOOLS+=	gmake

USE_LANGUAGES+=	c c++

# MAKE_JOBS_SAFE=		no

BUILD_DEPENDS+=	repo>=1.23:../../base/repo
BUILD_DEPENDS+=	dmidecode>=2.12:../../sysutils/dmidecode
BUILD_DEPENDS+=	go>=1.8:../../base/go18

MAKE_ENV+=	MAKETYPE="Unix Makefiles"

CFLAGS+=	-L/data/lib
CFLAGS+=	-Wl,-rpath,/data/lib
LDFLAGS+=	-L/data/lib
CXXFLAGS+=	-L/data/lib
CXXFLAGS+=	-Wl,-rpath,/data/lib

pre-extract:
	if [ ! -f ${DISTDIR}/couchbase-${VERSION}.tar.gz ]; then \
		mkdir -p ${WRKSRC}; \
		cd ${WRKSRC}; \
		repo init -u git://github.com/couchbase/manifest.git -m released/${VERSION}.xml; \
		repo sync; \
		cd ${WRKDIR}; tar -czf ${DISTDIR}/couchbase-${VERSION}.tar.gz --exclude-vcs couchbase-${VERSION}; \
	fi

do-extract:
	if [ ! -d ${WRKSRC} ]; then \
		tar -xzf ${DISTDIR}/couchbase-${VERSION}.tar.gz -C ${WRKDIR}; \
	fi

.include "../../devel/jemalloc/buildlink3.mk"
.include "../../devel/snappy/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../devel/libevent/buildlink3.mk"
.include "../../base/erlang19/buildlink3.mk"
.include "../../textproc/icu/buildlink3.mk"
.include "../../devel/cmake/buildlink3.mk"
.include "../../base/flatbuffers-c/buildlink3.mk"
.include "../../base/v8/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
