# $NetBSD: buildlink3.mk,v 1.12 2012/05/07 01:53:18 dholland Exp $

.include "../../base/php/extension_versions.mk"

BUILDLINK_TREE+=  php-json

.if !defined(PHP_JSON_BUILDLINK3_MK)
PHP_JSON_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.php-json+= ${PHP_PKG_PREFIX}-json>=${PHP_EXTENSION_VERSION.json}
BUILDLINK_ABI_DEPENDS.php-json+= ${PHP_PKG_PREFIX}-json>=${PHP_EXTENSION_VERSION.json}
BUILDLINK_PKGSRCDIR.php-json?= ../../base/php-json
BUILDLINK_INCDIRS.-php-json?= include/php/ext/json
.endif # PHP_JSON_BUILDLINK3_MK

BUILDLINK_TREE+=  -php-json
