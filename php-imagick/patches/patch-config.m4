$NetBSD$

--- config.m4.orig	2013-09-25 05:42:37.000000000 +0000
+++ config.m4
@@ -12,7 +12,7 @@ if test $PHP_IMAGICK != "no"; then
 
   AC_MSG_CHECKING(ImageMagick MagickWand API configuration program)
 
-  for i in $PHP_IMAGICK /usr/local /usr;
+  for i in $PHP_IMAGICK /usr/local /usr /opt/local /opt;
   do
     test -r $i/bin/MagickWand-config && IMAGICK_AFTER_BWC_BREAK=true && WAND_BINARY=$i/bin/MagickWand-config && break
   done
