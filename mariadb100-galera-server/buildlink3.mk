# $NetBSD: buildlink3.mk,v 1.5 2013/03/23 16:01:58 joerg Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
#  # vim: ts=8 sw=8 ft=make noet

BUILDLINK_TREE+=	mariadb-galera-server

.if !defined(MARIADB_GALERA_SERVER_BUILDLINK3_MK)
MARIADB_GALERA_SERVER_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.mariadb-galera-server+=	mariadb-galera-server>=10.0.17<10.1
BUILDLINK_ABI_DEPENDS.mariadb-galera-server?=	mariadb-galera-server>=10.0.17<10.1
BUILDLINK_PKGSRCDIR.mariadb-galera-server?=		../../base/mariadb100-galera-server
BUILDLINK_LIBDIRS.mariadb-galera-server?=		lib

#.include "../../base/mariadb100-galera-client/buildlink3.mk"
.endif	# MARIADB_GALERA_SERVER_BUILDLINK3_MK

BUILDLINK_TREE+=	-mariadb-galera-server
