# $NetBSD: buildlink3.mk,v 1.7 2009/03/20 19:24:17 joerg Exp $

BUILDLINK_TREE+=	libqb

.if !defined(LIBQB_BUILDLINK3_MK)
LIBQB_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libqb+=	libqb>=1.0
BUILDLINK_PKGSRCDIR.libqb?=	../../base/libqb
.endif # LIBQB_BUILDLINK3_MK

BUILDLINK_TREE+=	-libqb
