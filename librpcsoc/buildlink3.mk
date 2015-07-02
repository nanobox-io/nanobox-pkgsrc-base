# $NetBSD: buildlink3.mk,v 1.35 2013/04/06 11:06:52 rodent Exp $

BUILDLINK_TREE+=  librpcsoc

.if !defined(LIBRPCSOC_BUILDLINK3_MK)
LIBRPCSOC_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.librpcsoc+= librpcsoc>=1
BUILDLINK_PKGSRCDIR.librpcsoc?= ../../base/librpcsoc

.endif # LIBRPCSOC_BUILDLINK3_MK

BUILDLINK_TREE+=  -librpcsoc
