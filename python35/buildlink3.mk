# $NetBSD: buildlink3.mk,v 1.1 2014/05/09 02:27:14 wen Exp $

BUILDLINK_TREE+=	python

.if !defined(PYTHON_BUILDLINK3_MK)
PYTHON_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.python+=	python>=3.5
BUILDLINK_PKGSRCDIR.python?=		../../base/python35

.if defined(BUILDLINK_DEPMETHOD.python)
BUILDLINK_DEPMETHOD.python?=	${BUILDLINK_DEPMETHOD.python}
.endif

.include "../../mk/dlopen.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.endif # PYTHON_BUILDLINK3_MK

BUILDLINK_TREE+=	-python
