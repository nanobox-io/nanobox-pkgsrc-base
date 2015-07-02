# $NetBSD: buildlink3.mk,v 1.1 2013/02/13 21:00:10 adam Exp $

BUILDLINK_TREE+=	percona-xtradb-server

.if !defined(PERCONA_XTRADB_SERVER_BUILDLINK3_MK)
PERCONA_XTRADB_SERVER_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.percona-xtradb-server+=	percona-xtradb-server>=5.6.10
BUILDLINK_ABI_DEPENDS.percona-xtradb-server?=	percona-xtradb-server>=5.6.10
BUILDLINK_PKGSRCDIR.percona-xtradb-server?=	../../base/percona56-xtradb-server
BUILDLINK_LIBDIRS.percona-xtradb-server?=	lib

.endif	# PERCONA_XTRADB_SERVER_BUILDLINK3_MK

BUILDLINK_TREE+=	-percona-xtradb-server
