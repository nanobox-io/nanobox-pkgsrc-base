# $NetBSD$

.include "../../base/php/extension_versions.mk"

BUILDLINK_TREE+=	php-mbstring

.if !defined(PHP_MBSTRING_BUILDLINK3_MK)
PHP_MBSTRING_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.php-mbstring+=	${PHP_PKG_PREFIX}-mbstring>${PHP_EXTENSION_VERSION.mbstring}
BUILDLINK_PKGSRCDIR.php-mbstring?=	../../base/php-mbstring
BUILDLINK_DEPMETHOD.php-mbstring?=	build
.endif	# PHP_MBSTRING_BUILDLINK3_MK

BUILDLINK_TREE+=	-php-mbstring
