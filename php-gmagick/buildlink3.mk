# $NetBSD: buildlink3.mk,v 1.12 2012/05/07 01:53:18 dholland Exp $

.include "../../base/php/extension_versions.mk"

BUILDLINK_TREE+=  php-gmagick

.if !defined(PHP_GMAGICK_BUILDLINK3_MK)
PHP_GMAGICK_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.php-gmagick+= ${PHP_PKG_PREFIX}-gmagick>=${PHP_EXTENSION_VERSION.gmagick}
BUILDLINK_ABI_DEPENDS.php-gmagick+= ${PHP_PKG_PREFIX}-gmagick>=${PHP_EXTENSION_VERSION.gmagick}
BUILDLINK_PKGSRCDIR.php-gmagick?= ../../base/php-gmagick
BUILDLINK_INCDIRS.php-gmagick?= include/php/ext/gmagick
.endif # PHP_GMAGICK_BUILDLINK3_MK

BUILDLINK_TREE+=  -php-gmagick
