# $NetBSD: buildlink3.mk,v 1.7 2009/03/20 19:24:17 joerg Exp $

BUILDLINK_TREE+=	libdwarf

.if !defined(LIBDWARF_BUILDLINK3_MK)
LIBDWARF_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libdwarf+=	libdwarf>=20150507
BUILDLINK_PKGSRCDIR.libdwarf?=	../../base/libdwarf
.endif # LIBDWARF_BUILDLINK3_MK

BUILDLINK_TREE+=	-libdwarf
