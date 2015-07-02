# $NetBSD: buildlink3.mk,v 1.12 2012/05/07 01:53:18 dholland Exp $

.include "../../base/php/extension_versions.mk"

BUILDLINK_TREE+=  php-xml

.if !defined(PHP_XML_BUILDLINK3_MK)
PHP_XML_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.php-xml+= ${PHP_PKG_PREFIX}-xml-5.*
BUILDLINK_ABI_DEPENDS.php-xml+= ${PHP_PKG_PREFIX}-xml>=${PHP_EXTENSION_VERSION.xml}
BUILDLINK_PKGSRCDIR.php-xml?= ../../base/php-xml
BUILDLINK_INCDIRS.php-xml?= include/php/ext/xml
.endif # PHP_XML_BUILDLINK3_MK

BUILDLINK_TREE+=  -php-xml
