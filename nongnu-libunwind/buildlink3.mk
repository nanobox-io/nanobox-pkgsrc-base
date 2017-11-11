# $NetBSD: buildlink3.mk,v 1.7 2009/03/20 19:24:17 joerg Exp $

BUILDLINK_TREE+=	nongnu-libunwind

.if !defined(NONGNU_LIBUNWIND_BUILDLINK3_MK)
NONGNU_LIBUNWIND_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.nongnu-libunwind+=	nongnu-libunwind>=1.2
BUILDLINK_PKGSRCDIR.nongnu-libunwind?=	../../base/nongnu-libunwind
.endif # NONGNU_LIBUNWIND_BUILDLINK3_MK

BUILDLINK_TREE+=	-nongnu-libunwind
