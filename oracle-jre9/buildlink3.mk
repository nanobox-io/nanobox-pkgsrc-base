# $NetBSD: buildlink3.mk,v 1.1 2015/05/30 09:49:43 ryoon Exp $

BUILDLINK_TREE+=	oracle-jre9

.if !defined(ORACLE_JRE9_BUILDLINK3_MK)
ORACLE_JRE9_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.oracle-jre9+=		oracle-jre9-[0-9]*
BUILDLINK_ABI_DEPENDS.oracle-jre9+=		oracle-jre9>=9.0.1
BUILDLINK_PKGSRCDIR.oracle-jre9?=		../../base/oracle-jre9

CHECK_BUILTIN.oracle-jre9:=	yes
.include "../../base/oracle-jre9/builtin.mk"
CHECK_BUILTIN.oracle-jre9:=	no

.if !empty(USE_BUILTIN.oracle-jre9:M[yY][eE][sS])
BUILDLINK_JAVA_PREFIX.oracle-jre9=	${JAVAVM9}
.else
BUILDLINK_JAVA_PREFIX.oracle-jre9=	${PREFIX}/java/oracle-9
.endif

UNLIMIT_RESOURCES+=	datasize	# Must be at least 131204
.endif # ORACLE_JRE9_BUILDLINK3_MK

BUILDLINK_TREE+=	-oracle-jre9
