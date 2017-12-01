# $NetBSD: buildlink3.mk,v 1.1 2015/05/30 09:51:11 ryoon Exp $

BUILDLINK_TREE+=	oracle-jdk9

.if !defined(ORACLE_JDK9_BUILDLINK3_MK)
ORACLE_JDK9_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.oracle-jdk9+=	oracle-jdk9-[0-9]*
BUILDLINK_ABI_DEPENDS.oracle-jdk9+=	oracle-jdk9>=9.0.1
BUILDLINK_PKGSRCDIR.oracle-jdk9?=	../../base/oracle-jdk9
BUILDLINK_DEPMETHOD.oracle-jdk9?= build

BUILDLINK_PASSTHRU_DIRS+=	${BUILDLINK_JAVA_PREFIX.oracle-jre9}

.include "../../mk/bsd.fast.prefs.mk"

.if ${OPSYS} == "SunOS"
BUILDLINK_CPPFLAGS.oracle-jdk9=						\
	-I${BUILDLINK_JAVA_PREFIX.oracle-jre9}/include			\
	-I${BUILDLINK_JAVA_PREFIX.oracle-jre9}/include/solaris
.else
BUILDLINK_CPPFLAGS.oracle-jdk9=						\
	-I${BUILDLINK_JAVA_PREFIX.oracle-jre9}/include			\
	-I${BUILDLINK_JAVA_PREFIX.oracle-jre9}/include/linux
.endif

#CPPFLAGS+=	${BUILDLINK_CPPFLAGS.oracle-jdk9}
#CXXFLAGS+=      ${BUILDLINK_CPPFLAGS.oracle-jdk9}

BUILDLINK_DEPMETHOD.oracle-jre9?=	${BUILDLINK_DEPMETHOD.oracle-jdk9}
.include "../../base/oracle-jre9/buildlink3.mk"
.endif # ORACLE_JDK9_BUILDLINK3_MK

BUILDLINK_TREE+=	-oracle-jdk9
