$NetBSD$

--- config.m4.orig	2013-10-14 13:21:16.000000000 +0000
+++ config.m4
@@ -11,7 +11,7 @@ PHP_ARG_WITH(slang-dir, for the location
 
 if test "$PHP_NEWT" != "no"; then
 
-  SEARCH_PATH="/usr/local /usr"
+  SEARCH_PATH="/usr/local /usr /opt/local /opt"
   SEARCH_FOR="/include/newt.h"
   if test -r $PHP_NEWT/$SEARCH_FOR; then
      NEWT_DIR=$PHP_NEWT
@@ -31,7 +31,7 @@ if test "$PHP_NEWT" != "no"; then
   fi
 
   if test "$PHP_CURSES_DIR" != "no"; then
-    for i in $PHP_CURSES_DIR /usr/local /usr; do
+    for i in $PHP_CURSES_DIR /usr/local /usr /opt/local /opt; do
       if test -f $i/$PHP_LIBDIR/libncurses.$SHLIB_SUFFIX_NAME -o -f $i/$PHP_LIBDIR/libncurses.a; then
 				PHP_ADD_LIBRARY_WITH_PATH(ncurses, $i/$PHP_LIBDIR, NEWT_SHARED_LIBADD)
 				break
@@ -44,7 +44,7 @@ if test "$PHP_NEWT" != "no"; then
 	fi
 
   if test "$PHP_SLANG_DIR" != "no"; then
-    for i in $PHP_SLANG_DIR /usr/local /usr; do
+    for i in $PHP_SLANG_DIR /usr/local /usr /opt/local /opt; do
       if test -f $i/$PHP_LIBDIR/libslang.$SHLIB_SUFFIX_NAME -o -f $i/$PHP_LIBDIR/libslang.a; then
 				PHP_ADD_LIBRARY_WITH_PATH(slang, $i/$PHP_LIBDIR, NEWT_SHARED_LIBADD)
 				break
