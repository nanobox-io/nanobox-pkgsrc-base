BUILDLINK_TREE+=	erlang

.if !defined(ERLANG_BUILDLINK_MK)
ERLANG_BUILDLINK_MK:=

.if !defined(_ERLANGVERSION_MK)
.include "../../base/erlang/erlangversion.mk"
.endif

BUILDLINK_API_DEPENDS.erlang+=	erlang>=${ERLANG_VERSION}<${ERLANG_VERSION_NEXT}
BUILDLINK_ABI_DEPENDS.erlang?=  erlang>=${ERLANG_VERSION}
BUILDLINK_PKGSRCDIR.erlang?=    ${ERLANG_SRCDIR}

.endif # ERLANG_BUILDLINK_MK

BUILDLINK_TREE+=	-erlang

.include "../../databases/unixodbc/buildlink3.mk"
.include "../../databases/iodbc/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../devel/ncurses/buildlink3.mk"
