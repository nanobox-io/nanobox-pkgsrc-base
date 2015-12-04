# $NetBSD: buildlink3.mk,v 1.12 2012/05/07 01:53:18 dholland Exp $

.include "../../base/php/extension_versions.mk"

BUILDLINK_TREE+=  php-raphf

.if !defined(PHP_RAPHF_BUILDLINK3_MK)
PHP_RAPHF_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.php-raphf+= ${PHP_PKG_PREFIX}-raphf>=${PHP_EXTENSION_VERSION.raphf}
BUILDLINK_ABI_DEPENDS.php-raphf+= ${PHP_PKG_PREFIX}-raphf>=${PHP_EXTENSION_VERSION.raphf}
BUILDLINK_PKGSRCDIR.php-raphf?= ../../base/php-raphf
BUILDLINK_INCDIRS.php-raphf?= include/php/ext/raphf
.endif # PHP_RAPHF_BUILDLINK3_MK

BUILDLINK_TREE+=  -php-raphf
