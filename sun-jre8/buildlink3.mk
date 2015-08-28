# $NetBSD: buildlink3.mk,v 1.2 2013/10/16 16:48:29 richard Exp $

BUILDLINK_TREE+=	sun-jre8

.if !defined(SUN_JRE8_BUILDLINK3_MK)
SUN_JRE8_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.sun-jre8+=		sun-jre8-[0-9]*
BUILDLINK_ABI_DEPENDS.sun-jre8+=		sun-jre8>=8.0.9
BUILDLINK_PKGSRCDIR.sun-jre8?=		../../lang/sun-jre8

CHECK_BUILTIN.sun-jre8:=	yes
.include "../../lang/sun-jre8/builtin.mk"
CHECK_BUILTIN.sun-jre8:=	no

.if !empty(USE_BUILTIN.sun-jre8:M[yY][eE][sS])
BUILDLINK_JAVA_PREFIX.sun-jre8=	${JAVAVM8}
.else
BUILDLINK_JAVA_PREFIX.sun-jre8=	${PREFIX}/java/sun-8
.endif

UNLIMIT_RESOURCES+=	datasize	# Must be at least 131204
.endif # SUN_JRE8_BUILDLINK3_MK

BUILDLINK_TREE+=	-sun-jre8
