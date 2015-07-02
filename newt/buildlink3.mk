# $NetBSD: buildlink3.mk,v 1.12 2012/05/07 01:53:18 dholland Exp $

BUILDLINK_TREE+=  newt

.if !defined(NEWT_BUILDLINK3_MK)
NEWT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.newt+= newt-0.52.*
BUILDLINK_ABI_DEPENDS.newt+= newt>=0.52
BUILDLINK_PKGSRCDIR.newt?= ../../base/newt
.endif # NEWT_BUILDLINK3_MK

BUILDLINK_TREE+=  -newt
