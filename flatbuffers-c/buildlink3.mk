# $NetBSD: buildlink3.mk,v 1.10 2009/12/16 09:29:06 wiz Exp $

BUILDLINK_TREE+=	flatbuffers-c

.if !defined(FLATBUFFERS_C_BUILDLINK3_MK)
FLATBUFFERS_C_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.flatbuffers-c+=	flatbuffers-c>=1.6.0
BUILDLINK_ABI_DEPENDS.flatbuffers-c?=	flatbuffers-c>=1.6.0
BUILDLINK_PKGSRCDIR.flatbuffers-c?=	../../base/flatbuffers-c

.endif # FLATBUFFERS_C_BUILDLINK3_MK

BUILDLINK_TREE+=	-flatbuffers-c
