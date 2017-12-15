# $NetBSD: buildlink3.mk,v 1.33 2011/02/23 11:00:17 adam Exp $

BUILDLINK_TREE+=	mosquitto

.if !defined(MOSQUITTO_BUILDLINK3_MK)
MOSQUITTO_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.mosquitto+=	mosquitto>=1.4
BUILDLINK_ABI_DEPENDS.mosquitto+=	mosquitto>=1.4
BUILDLINK_PKGSRCDIR.mosquitto?=		../../base/mosquitto

.endif # MOSQUITTO_BUILDLINK3_MK

BUILDLINK_TREE+=	-mosquitto
