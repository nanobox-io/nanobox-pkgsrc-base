# $NetBSD: buildlink3.mk,v 1.6 2014/02/12 23:17:39 tron Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
#  # vim: ts=8 sw=8 ft=make noet

BUILDLINK_TREE+=	mariadb-galera-client

.if !defined(MARIADB_GALERA_CLIENT_BUILDLINK3_MK)
MARIADB_GALERA_CLIENT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.mariadb-galera-client+=	mariadb-galera-client>=10.0.17<10.1
BUILDLINK_ABI_DEPENDS.mariadb-galera-client+=	mariadb-galera-client>=10.0.17
BUILDLINK_PKGSRCDIR.mariadb-galera-client?=		../../base/mariadb100-galera-client
BUILDLINK_INCDIRS.mariadb-galera-client?=		include/mysql
BUILDLINK_LIBDIRS.mariadb-galera-client?=		lib

.include "../../devel/zlib/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.endif # MARIADB_GALERA_CLIENT_BUILDLINK3_MK

BUILDLINK_TREE+=	-mariadb-galera-client
