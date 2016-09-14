# $NetBSD: buildlink3.mk,v 1.10 2009/12/16 09:29:06 wiz Exp $

BUILDLINK_TREE+=	erlang

.if !defined(ERLANG_BUILDLINK3_MK)
ERLANG_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.erlang+=	erlang>=18
BUILDLINK_ABI_DEPENDS.erlang?=	erlang>=18
BUILDLINK_PKGSRCDIR.erlang?=	../../base/erlang18

.endif # ERLANG_BUILDLINK3_MK

BUILDLINK_TREE+=	-erlang

.include "../../databases/unixodbc/buildlink3.mk"
.include "../../databases/iodbc/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../devel/ncurses/buildlink3.mk"
