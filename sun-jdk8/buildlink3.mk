# $NetBSD: buildlink3.mk,v 1.3 2013/10/16 16:48:55 richard Exp $

BUILDLINK_TREE+=	sun-jdk8

.if !defined(SUN_JDK8_BUILDLINK3_MK)
SUN_JDK8_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.sun-jdk8+=	sun-jdk8-[0-9]*
BUILDLINK_ABI_DEPENDS.sun-jdk8+=	sun-jdk8>=8.0.9
BUILDLINK_PKGSRCDIR.sun-jdk8?=	../../base/sun-jdk8
BUILDLINK_DEPMETHOD.sun-jdk8?= build

BUILDLINK_PASSTHRU_DIRS+=	${BUILDLINK_JAVA_PREFIX.sun-jre8}

.include "../../mk/bsd.fast.prefs.mk"

.if ${OPSYS} == "SunOS"
BUILDLINK_CPPFLAGS.sun-jdk8=						\
	-I${BUILDLINK_JAVA_PREFIX.sun-jre8}/include			\
	-I${BUILDLINK_JAVA_PREFIX.sun-jre8}/include/solaris
.else
BUILDLINK_CPPFLAGS.sun-jdk8=						\
	-I${BUILDLINK_JAVA_PREFIX.sun-jre8}/include			\
	-I${BUILDLINK_JAVA_PREFIX.sun-jre8}/include/linux
.endif

BUILDLINK_DEPMETHOD.sun-jre8?=	${BUILDLINK_DEPMETHOD.sun-jdk8}
.include "../../base/sun-jre8/buildlink3.mk"
.endif # SUN_JDK8_BUILDLINK3_MK

BUILDLINK_TREE+=	-sun-jdk8
