# $NetBSD: buildlink3.mk,v 1.12 2012/05/07 01:53:18 dholland Exp $

.include "../../base/php/extension_versions.mk"

BUILDLINK_TREE+=  php-filter

.if !defined(PHP_FILTER_BUILDLINK3_MK)
PHP_FILTER_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.php-filter+= ${PHP_PKG_PREFIX}-filter>=${PHP_EXTENSION_VERSION.filter}
BUILDLINK_ABI_DEPENDS.php-filter+= ${PHP_PKG_PREFIX}-filter>=${PHP_EXTENSION_VERSION.filter}
BUILDLINK_PKGSRCDIR.php-filter?= ../../base/php-filter
BUILDLINK_INCDIRS.php-filter?= include/php/ext/filter
.endif # PHP_FILTER_BUILDLINK3_MK

BUILDLINK_TREE+=  -php-filter
