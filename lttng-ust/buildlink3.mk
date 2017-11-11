# $NetBSD: buildlink3.mk,v 1.7 2009/03/20 19:24:17 joerg Exp $

BUILDLINK_TREE+=	lttng-ust

.if !defined(LTTNG_UST_BUILDLINK3_MK)
LTTNG_UST_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.lttng-ust+=	lttng-ust>=2.10
BUILDLINK_PKGSRCDIR.lttng-ust?=	../../base/lttng-ust
.endif # LTTNG_UST_BUILDLINK3_MK

BUILDLINK_TREE+=	-lttng-ust
