# $NetBSD: buildlink3.mk,v 1.33 2011/02/23 11:00:17 adam Exp $

BUILDLINK_TREE+=	gperftools

.if !defined(GPERFTOOLS_BUILDLINK3_MK)
GPERFTOOLS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gperftools+=	gperftools>=2.4
BUILDLINK_ABI_DEPENDS.gperftools+=	gperftools>=2.4
BUILDLINK_PKGSRCDIR.gperftools?=		../../base/gperftools

.endif # GPERFTOOLS_BUILDLINK3_MK

BUILDLINK_TREE+=	-gperftools
