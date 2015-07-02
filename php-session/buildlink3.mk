# $NetBSD: buildlink3.mk,v 1.12 2012/05/07 01:53:18 dholland Exp $

.include "../../base/php/extension_versions.mk"

BUILDLINK_TREE+=  php-session

.if !defined(PHP_SESSION_BUILDLINK3_MK)
PHP_SESSION_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.php-session+= ${PHP_PKG_PREFIX}-session-5.*
BUILDLINK_ABI_DEPENDS.php-session+= ${PHP_PKG_PREFIX}-session>=${PHP_EXTENSION_VERSION.session}
BUILDLINK_PKGSRCDIR.php-session?= ../../base/php-session
BUILDLINK_INCDIRS.php-session?= include/php/ext/session
.endif # PHP_SESSION_BUILDLINK3_MK

BUILDLINK_TREE+=  -php-session
