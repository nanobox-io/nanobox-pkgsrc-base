# $NetBSD: buildlink3.mk,v 1.33 2011/02/23 11:00:17 adam Exp $

BUILDLINK_TREE+=	libattr

.if !defined(LIBATTR_BUILDLINK3_MK)
LIBATTR_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libattr+=	libattr>=2.4
BUILDLINK_ABI_DEPENDS.libattr+=	libattr>=2.4
BUILDLINK_PKGSRCDIR.libattr?=		../../base/libattr

.endif # LIBATTR_BUILDLINK3_MK

BUILDLINK_TREE+=	-libattr
