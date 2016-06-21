$NetBSD$

--- ext/gd/config.m4.orig	2014-08-13 19:22:50.000000000 +0000
+++ ext/gd/config.m4
@@ -45,18 +45,7 @@ dnl Checks for the configure options
 dnl
 
 AC_DEFUN([PHP_GD_ZLIB],[
-	if test "$PHP_ZLIB_DIR" != "no" && test "$PHP_ZLIB_DIR" != "yes"; then
-		if test -f "$PHP_ZLIB_DIR/include/zlib/zlib.h"; then
-			PHP_ZLIB_DIR="$PHP_ZLIB_DIR"
-			PHP_ZLIB_INCDIR="$PHP_ZLIB_DIR/include/zlib"
-		elif test -f "$PHP_ZLIB_DIR/include/zlib.h"; then
-			PHP_ZLIB_DIR="$PHP_ZLIB_DIR"
-			PHP_ZLIB_INCDIR="$PHP_ZLIB_DIR/include"
-		else
-			AC_MSG_ERROR([Can't find zlib headers under "$PHP_ZLIB_DIR"])
-		fi
-	else
-		for i in /usr/local /usr; do
+		for i in "$PHP_ZLIB_DIR" /usr/local /usr @PREFIX@; do
 			if test -f "$i/include/zlib/zlib.h"; then
 				PHP_ZLIB_DIR="$i"
 				PHP_ZLIB_INCDIR="$i/include/zlib"
@@ -65,13 +54,12 @@ AC_DEFUN([PHP_GD_ZLIB],[
 				PHP_ZLIB_INCDIR="$i/include"
 			fi
 		done
-	fi
 ])
 
 AC_DEFUN([PHP_GD_JPEG],[
   if test "$PHP_JPEG_DIR" != "no"; then
 
-    for i in $PHP_JPEG_DIR /usr/local /usr; do
+    for i in $PHP_JPEG_DIR /usr/local /usr @PREFIX@; do
       test -f $i/include/jpeglib.h && GD_JPEG_DIR=$i && break
     done
 
@@ -96,7 +84,7 @@ AC_DEFUN([PHP_GD_JPEG],[
 AC_DEFUN([PHP_GD_PNG],[
   if test "$PHP_PNG_DIR" != "no"; then
 
-    for i in $PHP_PNG_DIR /usr/local /usr; do
+    for i in $PHP_PNG_DIR /usr/local /usr @PREFIX@; do
       test -f $i/include/png.h && GD_PNG_DIR=$i && break
     done
 
@@ -108,13 +96,13 @@ AC_DEFUN([PHP_GD_PNG],[
       AC_MSG_ERROR([PNG support requires ZLIB. Use --with-zlib-dir=<DIR>])
     fi
 
-    PHP_CHECK_LIBRARY(png,png_write_image,
+    PHP_CHECK_LIBRARY(png16,png_write_image,
     [
       PHP_ADD_INCLUDE($GD_PNG_DIR/include)
       PHP_ADD_LIBRARY_WITH_PATH(z, $PHP_ZLIB_DIR/$PHP_LIBDIR, GD_SHARED_LIBADD)
-      PHP_ADD_LIBRARY_WITH_PATH(png, $GD_PNG_DIR/$PHP_LIBDIR, GD_SHARED_LIBADD)
+      PHP_ADD_LIBRARY_WITH_PATH(png16, $GD_PNG_DIR/$PHP_LIBDIR, GD_SHARED_LIBADD)
     ],[
-      AC_MSG_ERROR([Problem with libpng.(a|so) or libz.(a|so). Please check config.log for more information.])
+      AC_MSG_ERROR([Problem with libpng16.(a|so) or libz.(a|so). Please check config.log for more information.])
     ],[
       -L$PHP_ZLIB_DIR/$PHP_LIBDIR -lz -L$GD_PNG_DIR/$PHP_LIBDIR
     ])
@@ -127,7 +115,7 @@ AC_DEFUN([PHP_GD_PNG],[
 AC_DEFUN([PHP_GD_XPM],[
   if test "$PHP_XPM_DIR" != "no"; then
 
-    for i in $PHP_XPM_DIR /usr/local /usr/X11R6 /usr; do
+    for i in $PHP_XPM_DIR /usr/local /usr @PREFIX@/X11R6 /usr; do
       test -f $i/$PHP_LIBDIR/libXpm.$SHLIB_SUFFIX_NAME || test -f $i/$PHP_LIBDIR/libXpm.a && GD_XPM_DIR=$i && break
     done
 
@@ -161,7 +149,7 @@ AC_DEFUN([PHP_GD_XPM],[
 AC_DEFUN([PHP_GD_FREETYPE2],[
   if test "$PHP_FREETYPE_DIR" != "no"; then
 
-    for i in $PHP_FREETYPE_DIR /usr/local /usr; do
+    for i in $PHP_FREETYPE_DIR /usr/local /usr @PREFIX@; do
       if test -f "$i/include/freetype2/freetype/freetype.h"; then
         FREETYPE2_DIR=$i
         FREETYPE2_INC_DIR=$i/include/freetype2
@@ -194,7 +182,7 @@ AC_DEFUN([PHP_GD_FREETYPE2],[
 AC_DEFUN([PHP_GD_T1LIB],[
   if test "$PHP_T1LIB" != "no"; then
 
-    for i in $PHP_T1LIB /usr/local /usr; do
+    for i in $PHP_T1LIB /usr/local /usr @PREFIX@; do
       test -f "$i/include/t1lib.h" && GD_T1_DIR=$i && break
     done
 
