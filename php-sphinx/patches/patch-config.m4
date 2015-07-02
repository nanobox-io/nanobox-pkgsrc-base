$NetBSD$

--- config.m4.orig	2013-04-04 11:58:36.000000000 +0000
+++ config.m4
@@ -5,7 +5,7 @@ PHP_ARG_WITH(sphinx, for sphinx support,
 
 if test "$PHP_SPHINX" != "no"; then
 
-  SEARCH_PATH="/usr/local /usr /local /opt"
+  SEARCH_PATH="/usr/local /usr /local /opt /opt/local"
   SEARCH_FOR="/include/sphinxclient.h"
 
   if test "$PHP_SPHINX" = "yes"; then
