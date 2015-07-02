$NetBSD$

--- ext/opcache/config.m4.orig	2014-08-27 13:31:35.000000000 +0000
+++ ext/opcache/config.m4
@@ -359,7 +359,7 @@ AC_TRY_RUN([
     AC_MSG_RESULT("yes")
 ], AC_MSG_RESULT("no") )
 
-if test "$flock_type" == "unknown"; then
+if test "$flock_type" = "unknown"; then
 	AC_MSG_ERROR([Don't know how to define struct flock on this system[,] set --enable-opcache=no])
 fi
 
