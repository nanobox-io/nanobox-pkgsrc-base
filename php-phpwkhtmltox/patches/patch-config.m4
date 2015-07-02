$NetBSD$

--- config.m4.orig	2015-04-22 16:19:59.061026678 +0000
+++ config.m4
@@ -2,7 +2,7 @@ PHP_ARG_WITH(phpwkhtmltox, [for libwkhtm
 [  --with-phpwkhtmltox=[DIR]     Include libwkhtmltox support])
 
 if test "$PHP_PHPWKHTMLTOX" != "no"; then
-    for i in $PHP_PHPWKHTMLTOX /usr /usr/local /opt; do
+    for i in $PHP_PHPWKHTMLTOX /usr/local /usr /opt; do
         if test -f $i/include/wkhtmltox/pdf.h; then
             WKHTMLTOX_LIB_DIR=$i/lib
             WKHTMLTOX_INC_DIR=$i/include
@@ -26,4 +26,4 @@ if test "$PHP_PHPWKHTMLTOX" != "no"; the
     PHP_SUBST(PHPWKHTMLTOX_SHARED_LIBADD)
     PHP_ADD_INCLUDE($WKHTMLTOX_INC_DIR)
     PHP_NEW_EXTENSION(phpwkhtmltox, phpwkhtmltox.c, $ext_shared)
-fi
\ No newline at end of file
+fi
