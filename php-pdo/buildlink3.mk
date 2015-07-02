# $NetBSD: buildlink3.mk,v 1.12 2012/05/07 01:53:18 dholland Exp $

.include "../../base/php/extension_versions.mk"

BUILDLINK_TREE+=	php-pdo

.if !defined(PHP_PDO_BUILDLINK3_MK)
PHP_PDO_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.php-pdo+=	${PHP_PKG_PREFIX}-pdo-5.*
BUILDLINK_ABI_DEPENDS.php-pdo+=	${PHP_PKG_PREFIX}-pdo>=${PHP_EXTENSION_VERSION.pdo}
BUILDLINK_PKGSRCDIR.php-pdo?=	../../base/php-pdo
BUILDLINK_INCDIRS.php-pdo?=	include/php/ext/pdo
.endif # PHP_PDO_BUILDLINK3_MK

BUILDLINK_TREE+=	-php-pdo
