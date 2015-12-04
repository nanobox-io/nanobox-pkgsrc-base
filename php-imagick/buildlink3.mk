# $NetBSD: buildlink3.mk,v 1.12 2012/05/07 01:53:18 dholland Exp $

.include "../../base/php/extension_versions.mk"

BUILDLINK_TREE+=  php-imagick

.if !defined(PHP_IMAGICK_BUILDLINK3_MK)
PHP_IMAGICK_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.php-imagick+= ${PHP_PKG_PREFIX}-imagick>=${PHP_EXTENSION_VERSION.imagick}
BUILDLINK_ABI_DEPENDS.php-imagick+= ${PHP_PKG_PREFIX}-imagick>=${PHP_EXTENSION_VERSION.imagick}
BUILDLINK_PKGSRCDIR.php-imagick?= ../../base/php-imagick
BUILDLINK_INCDIRS.php-imagick?= include/php/ext/imagick
.endif # PHP_IMAGICK_BUILDLINK3_MK

BUILDLINK_TREE+=  -php-imagick
