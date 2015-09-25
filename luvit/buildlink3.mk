# $NetBSD: buildlink3.mk,v 1.10 2009/12/16 09:29:06 wiz Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

BUILDLINK_TREE+=	luvit

.if !defined(LUVIT_BUILDLINK3_MK)
LUVIT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.luvit+=	luvit>=0.10.0
BUILDLINK_ABI_DEPENDS.luvit?=	luvit>=0.10.0
BUILDLINK_PKGSRCDIR.luvit?=		../../base/luvit

.endif # LUVIT_BUILDLINK3_MK

BUILDLINK_TREE+=	-luvit
