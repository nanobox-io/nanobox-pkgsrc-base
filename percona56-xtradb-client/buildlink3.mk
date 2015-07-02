# $NetBSD: buildlink3.mk,v 1.2 2014/02/12 23:17:39 tron Exp $

BUILDLINK_TREE+=	percona-xtradb-client

.if !defined(PERCONA_XTRADB_CLIENT_BUILDLINK3_MK)
PERCONA_XTRADB_CLIENT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.percona-xtradb-client+=	percona-xtradb-client>=5.6.10
BUILDLINK_ABI_DEPENDS.percona-xtradb-client+=	percona-xtradb-client>=5.6.15nb1
BUILDLINK_PKGSRCDIR.percona-xtradb-client?=	../../base/percona56-xtradb-client
BUILDLINK_INCDIRS.percona-xtradb-client?=	include/mysql
BUILDLINK_LIBDIRS.percona-xtradb-client?=	lib

.include "../../devel/zlib/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.endif # PERCONA_XTRADB_CLIENT_BUILDLINK3_MK

BUILDLINK_TREE+=	-percona-xtradb-client
