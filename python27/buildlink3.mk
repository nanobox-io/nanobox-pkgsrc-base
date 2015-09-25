# $NetBSD: buildlink3.mk,v 1.5 2012/05/07 01:53:42 dholland Exp $

BUILDLINK_TREE+=	python

.if !defined(PYTHON_BUILDLINK3_MK)
PYTHON_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.python+=	python>=2.7
BUILDLINK_ABI_DEPENDS.python+=		python>=2.7.1nb2
BUILDLINK_PKGSRCDIR.python?=		../../base/python27

.if defined(BUILDLINK_DEPMETHOD.python)
BUILDLINK_DEPMETHOD.python?=	${BUILDLINK_DEPMETHOD.python}
.endif

.include "../../mk/dlopen.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.endif # PYTHON_BUILDLINK3_MK

BUILDLINK_TREE+=	-python
