# $NetBSD$

BUILDLINK_TREE+=			sphinxsearch-client

.if !defined(SPHINXSEARCH_CLIENT_BUILDLINK3_MK)
SPHINXSEARCH_CLIENT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.sphinxsearch-client+=	sphinxsearch-client>=0.9.9
BUILDLINK_PKGSRCDIR.sphinxsearch-client?=	../../base/sphinxsearch-client

.endif	# SPHINXSEARCH_CLIENT_BUILDLINK3_MK

BUILDLINK_TREE+=			-sphinxsearch-client
