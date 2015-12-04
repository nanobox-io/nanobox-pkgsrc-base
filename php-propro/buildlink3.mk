# $NetBSD: buildlink3.mk,v 1.12 2012/05/07 01:53:18 dholland Exp $

.include "../../base/php/extension_versions.mk"

BUILDLINK_TREE+=  php-propro

.if !defined(PHP_PROPRO_BUILDLINK3_MK)
PHP_PROPRO_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.php-propro+= ${PHP_PKG_PREFIX}-propro>=${PHP_EXTENSION_VERSION.propro}
BUILDLINK_ABI_DEPENDS.php-propro+= ${PHP_PKG_PREFIX}-propro>=${PHP_EXTENSION_VERSION.propro}
BUILDLINK_PKGSRCDIR.php-propro?= ../../base/php-propro
BUILDLINK_INCDIRS.php-propro?= include/php/ext/propro
.endif # PHP_PROPRO_BUILDLINK3_MK

BUILDLINK_TREE+=  -php-propro
