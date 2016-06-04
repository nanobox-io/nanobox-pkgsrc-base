# $NetBSD$

PKGNAME=	${DISTNAME:C/-/95-contrib-/}
COMMENT=	Contrib subtree of tools and plug-ins

.include "../../base/postgresql95/Makefile.common"

# Override the default from bsd.prefs.mk
PGSQL_VERSION= 95

DEPENDS+=	postgresql95-server>=${PKGVERSION_NOREV}:../../base/postgresql95-server

BUILD_MAKE_FLAGS=	PGXS=1

CONTRIB_DIRS=	btree_gin chkpass cube dict_int dict_xsyn		\
		earthdistance intagg oid2name pageinspect pg_freespacemap	\
		pg_trgm pgrowlocks seg spi sslinfo tablefunc		\
		tsearch2 vacuumlo xml2

.if !empty(PGSQL_VERSION:M9[0-9])
CONTRIB_DIRS+=	passwordcheck
.endif
.if !empty(PGSQL_VERSION:M9[1-9])
CONTRIB_DIRS+=	auth_delay file_fdw
.endif
.if !empty(PGSQL_VERSION:M9[2-9])
CONTRIB_DIRS+=	tcn
.endif
.if !empty(PGSQL_VERSION:M9[3-9])
CONTRIB_DIRS+=	postgres_fdw
.endif
.if !empty(PGSQL_VERSION:M9[4-9])
CONTRIB_DIRS+=	pg_prewarm test_decoding
.endif

.for dir in ${CONTRIB_DIRS}
BUILD_DIRS+=		contrib/${dir}
.endfor

BUILDLINK_INCDIRS.libxml2+=		include/libxml2
BUILDLINK_INCDIRS.${PGSQL_TYPE}+=	include/postgresql/server		\
					include/postgresql/server/libpq

PLIST_SRC=	PLIST.pg${PGSQL_VERSION}

.include "../../base/postgresql95-client/buildlink3.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
