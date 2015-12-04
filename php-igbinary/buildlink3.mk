# $NetBSD: buildlink3.mk,v 1.12 2012/05/07 01:53:18 dholland Exp $

.include "../../base/php/extension_versions.mk"

BUILDLINK_TREE+=  php-igbinary

.if !defined(PHP_IGBINARY_BUILDLINK3_MK)
PHP_IGBINARY_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.php-igbinary+= ${PHP_PKG_PREFIX}-igbinary>=${PHP_EXTENSION_VERSION.igbinary}
BUILDLINK_ABI_DEPENDS.php-igbinary+= ${PHP_PKG_PREFIX}-igbinary>=${PHP_EXTENSION_VERSION.igbinary}
BUILDLINK_PKGSRCDIR.php-igbinary?= ../../base/php-igbinary
BUILDLINK_INCDIRS.php-igbinary?= include/php/ext/igbinary
.endif # PHP_IGBINARY_BUILDLINK3_MK

BUILDLINK_TREE+=  -php-igbinary
