# $NetBSD: buildlink3.mk,v 1.33 2011/02/23 11:00:17 adam Exp $

BUILDLINK_TREE+=	libacl

.if !defined(LIBACL_BUILDLINK3_MK)
LIBACL_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libacl+=	libacl>=2.2
BUILDLINK_ABI_DEPENDS.libacl+=	libacl>=2.2
BUILDLINK_PKGSRCDIR.libacl?=		../../base/libacl

.endif # LIBACL_BUILDLINK3_MK

BUILDLINK_TREE+=	-libacl
