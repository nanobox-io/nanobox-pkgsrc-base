# $NetBSD: buildlink3.mk,v 1.6 2014/02/12 23:17:39 tron Exp $

BUILDLINK_TREE+=	percona-xtradb-client

.if !defined(PERCONA_XTRADB_CLIENT_BUILDLINK3_MK)
PERCONA_XTRADB_CLIENT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.percona-xtradb-client+=	percona-xtradb-client>=5.5.10<5.6
BUILDLINK_ABI_DEPENDS.percona-xtradb-client+=	percona-xtradb-client>=5.5.36nb1
BUILDLINK_PKGSRCDIR.percona-xtradb-client?=	../../base/perconal55-xtradb-client
BUILDLINK_INCDIRS.percona-xtradb-client?=	include/mysql
BUILDLINK_LIBDIRS.percona-xtradb-client?=	lib

.include "../../devel/zlib/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.endif # PERCONA_XTRADB_CLIENT_BUILDLINK3_MK

BUILDLINK_TREE+=	-percona-xtradb-client
