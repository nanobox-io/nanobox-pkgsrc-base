# $NetBSD: buildlink3.mk,v 1.5 2013/03/23 16:01:58 joerg Exp $

BUILDLINK_TREE+=	mariadb-galera-server

.if !defined(MARIADB_GALERA_SERVER_BUILDLINK3_MK)
MARIADB_GALERA_SERVER_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.mariadb-galera-server+=	mariadb-galera-server>=5.5.11<5.6
BUILDLINK_ABI_DEPENDS.mariadb-galera-server?=	mariadb-galera-server>=5.5.29nb1<5.6
BUILDLINK_PKGSRCDIR.mariadb-galera-server?=	../../base/mariadb55-galera-server
BUILDLINK_LIBDIRS.mariadb-galera-server?=	lib

#.include "../../base/mariadb55-galera-client/buildlink3.mk"
.endif	# MARIADB_GALERA_SERVER_BUILDLINK3_MK

BUILDLINK_TREE+=	-mariadb-galera-server
