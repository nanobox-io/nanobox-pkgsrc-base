# $NetBSD: buildlink3.mk,v 1.5 2013/03/23 16:01:58 joerg Exp $

BUILDLINK_TREE+=	percona-xtradb-server

.if !defined(PERCONA_XTRADB_SERVER_BUILDLINK3_MK)
PERCONA_XTRADB_SERVER_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.percona-xtradb-server+=	percona-xtradb-server>=5.5.11<5.6
BUILDLINK_ABI_DEPENDS.percona-xtradb-server?=	percona-xtradb-server>=5.5.29nb1<5.6
BUILDLINK_PKGSRCDIR.percona-xtradb-server?=	../../base/percona55-xtradb-server
BUILDLINK_LIBDIRS.percona-xtradb-server?=	lib

#.include "../../base/mysql55-client/buildlink3.mk"
.endif	# PERCONA_XTRADB_SERVER_BUILDLINK3_MK

BUILDLINK_TREE+=	-percona-xtradb-server
