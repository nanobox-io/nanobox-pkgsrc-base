$NetBSD$

--- config.m4.orig	2013-01-11 13:51:24.000000000 +0000
+++ config.m4
@@ -3,7 +3,7 @@ PHP_ARG_WITH(mogilefs, for mogilefs supp
 
 
 if test "$PHP_MOGILEFS" != "no"; then
-	paths="/usr /usr/local /sw"
+	paths="/usr /usr/local /sw @PREFIX@"
 
 	for path in $paths; do
 		if test -x "$path/bin/xml2-config"; then
