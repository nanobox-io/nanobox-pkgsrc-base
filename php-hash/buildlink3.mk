# $NetBSD: buildlink3.mk,v 1.12 2012/05/07 01:53:18 dholland Exp $

.include "../../base/php/extension_versions.mk"

BUILDLINK_TREE+=  php-hash

.if !defined(PHP_HASH_BUILDLINK3_MK)
PHP_HASH_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.php-hash+= ${PHP_PKG_PREFIX}-hash>=${PHP_EXTENSION_VERSION.hash}
BUILDLINK_ABI_DEPENDS.php-hash+= ${PHP_PKG_PREFIX}-hash>=${PHP_EXTENSION_VERSION.hash}
BUILDLINK_PKGSRCDIR.php-hash?= ../../base/php-hash
BUILDLINK_INCDIRS.php-hash?= include/php/ext/hash
.endif # PHP_HASH_BUILDLINK3_MK

BUILDLINK_TREE+=  -php-hash
