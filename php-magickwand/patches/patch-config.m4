$NetBSD$

--- config.m4.orig	2013-02-09 15:19:05.000000000 +0000
+++ config.m4
@@ -3,30 +3,30 @@ PHP_ARG_WITH(magickwand, whether to enab
 
 if test $PHP_MAGICKWAND != "no"; then
 
-    if test -r $PHP_MAGICKWAND/bin/MagickWand-config; then
+    if test -r $PHP_MAGICKWAND/bin/MagickWand-config6; then
         WAND_CONFIG_PATH=$PHP_MAGICKWAND/bin
     else
-        AC_MSG_CHECKING(MagickWand-config in default path)
+        AC_MSG_CHECKING(MagickWand-config6 in default path)
 
-        for i in /usr/local /usr;
+        for i in /usr/local /usr /data /opt/local;
         do
-            test -r $i/bin/MagickWand-config && WAND_CONFIG_PATH=$i/bin && break
+            test -r $i/bin/MagickWand-config6 && WAND_CONFIG_PATH=$i/bin && break
         done
 
         if test -z "$WAND_CONFIG_PATH"; then
-            for i in $PHP_MAGICKWAND /usr/local /usr;
+            for i in $PHP_MAGICKWAND /usr/local /usr /data /opt/local;
             do
-                test -r $i/MagickWand-config && WAND_CONFIG_PATH=$i && break
+                test -r $i/MagickWand-config6 && WAND_CONFIG_PATH=$i && break
             done
         fi
         if test -z "$WAND_CONFIG_PATH"; then
-            AC_MSG_ERROR(Cannot locate configuration program MagickWand-config)
+            AC_MSG_ERROR(Cannot locate configuration program MagickWand-config6)
         else
             AC_MSG_RESULT(found in $WAND_CONFIG_PATH)
         fi
     fi
 
-		IMAGEMAGICK_VERSION_ORIG=`$WAND_CONFIG_PATH/MagickWand-config --version`
+		IMAGEMAGICK_VERSION_ORIG=`$WAND_CONFIG_PATH/MagickWand-config6 --version`
 		IMAGEMAGICK_VERSION_MASK=`echo ${IMAGEMAGICK_VERSION_ORIG} | awk 'BEGIN { FS = "."; } { printf "%d", ($1 * 1000 + $2) * 1000 + $3;}'`
 
 
@@ -64,16 +64,16 @@ if test $PHP_MAGICKWAND != "no"; then
 		AC_DEFINE(HAVE_MAGICKWAND,1,[ ])
 
     export ORIG_PKG_CONFIG_PATH="$PKG_CONFIG_PATH"
-    export PKG_CONFIG_PATH="`$WAND_CONFIG_PATH/MagickWand-config --prefix`/lib/pkgconfig/"
+    export PKG_CONFIG_PATH="`$WAND_CONFIG_PATH/MagickWand-config6 --prefix`/lib/pkgconfig/"
 
 		PHP_ADD_INCLUDE($WAND_DIR/include/ImageMagick)
-		AC_MSG_CHECKING(MagickWand-config --cppflags)
-		WAND_CPPFLAGS="`$WAND_CONFIG_PATH/MagickWand-config --cppflags`"
+		AC_MSG_CHECKING(MagickWand-config6 --cppflags)
+		WAND_CPPFLAGS="`$WAND_CONFIG_PATH/MagickWand-config6 --cppflags`"
 		AC_MSG_RESULT($WAND_CPPFLAGS)
 		PHP_EVAL_INCLINE($WAND_CPPFLAGS)
 
-		AC_MSG_CHECKING(MagickWand-config --libs)
-		WAND_LIBS="`$WAND_CONFIG_PATH/MagickWand-config --libs`"
+		AC_MSG_CHECKING(MagickWand-config6 --libs)
+		WAND_LIBS="`$WAND_CONFIG_PATH/MagickWand-config6 --libs`"
 		AC_MSG_RESULT($WAND_LIBS)
 		PHP_EVAL_LIBLINE($WAND_LIBS, MAGICKWAND_SHARED_LIBADD)
     export PKG_CONFIG_PATH="$ORIG_PKG_CONFIG_PATH"
