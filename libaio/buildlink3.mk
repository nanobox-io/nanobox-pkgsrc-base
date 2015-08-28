# $NetBSD: buildlink3.mk,v 1.33 2011/02/23 11:00:17 adam Exp $

BUILDLINK_TREE+=	libaio

.if !defined(LIBAIO_BUILDLINK3_MK)
LIBAIO_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libaio+=	libaio>=0.3
BUILDLINK_ABI_DEPENDS.libaio+=	libaio>=0.3
BUILDLINK_PKGSRCDIR.libaio?=		../../base/libaio

.endif # LIBAIO_BUILDLINK3_MK

BUILDLINK_TREE+=	-libaio
