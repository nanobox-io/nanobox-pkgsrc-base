$NetBSD$

--- config.m4.orig	2013-02-09 15:19:05.000000000 +0000
+++ config.m4
@@ -8,13 +8,13 @@ if test $PHP_MAGICKWAND != "no"; then
     else
         AC_MSG_CHECKING(MagickWand-config in default path)
 
-        for i in /usr/local /usr;
+        for i in /usr/local /usr /opt/local;
         do
             test -r $i/bin/MagickWand-config && WAND_CONFIG_PATH=$i/bin && break
         done
 
         if test -z "$WAND_CONFIG_PATH"; then
-            for i in $PHP_MAGICKWAND /usr/local /usr;
+            for i in $PHP_MAGICKWAND /usr/local /usr /opt/local;
             do
                 test -r $i/MagickWand-config && WAND_CONFIG_PATH=$i && break
             done
