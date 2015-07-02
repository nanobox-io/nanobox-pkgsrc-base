# $NetBSD: buildlink3.mk,v 1.6 2014/02/12 23:17:39 tron Exp $

BUILDLINK_TREE+=	mariadb-galera-client

.if !defined(MARIADB_GALERA_CLIENT_BUILDLINK3_MK)
MARIADB_GALERA_CLIENT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.mariadb-galera-client+=	mariadb-galera-client>=5.5.10<5.6
BUILDLINK_ABI_DEPENDS.mariadb-galera-client+=	mariadb-galera-client>=5.5.36nb1
BUILDLINK_PKGSRCDIR.mariadb-galera-client?=	../../base/mariadb55-galera-client
BUILDLINK_INCDIRS.mariadb-galera-client?=	include/mysql
BUILDLINK_LIBDIRS.mariadb-galera-client?=	lib

.include "../../devel/zlib/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.endif # MARIADB_GALERA_CLIENT_BUILDLINK3_MK

BUILDLINK_TREE+=	-mariadb-galera-client
