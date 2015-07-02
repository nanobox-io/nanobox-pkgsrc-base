$NetBSD$

--- config.m4.orig	1970-01-01 09:13:08.000000000 +0000
+++ config.m4
@@ -5,7 +5,7 @@ PHP_ARG_WITH(gnupg, for gnupg support,
 [  --with-gnupg[=dir]       Include gnupg support])
 
 if test "$PHP_GNUPG" != "no"; then
-  SEARCH_PATH="/usr/local/include /usr/include /usr/local/include/gpgme/ /usr/include/gpgme/"
+  SEARCH_PATH="/usr/local/include /usr/include /usr/local/include/gpgme/ /usr/include/gpgme/ /opt/local/include /opt/local/include/gpgme/ @PREFIX@/include @PREFIX@/include/gpgme/"
   SEARCH_FOR="gpgme.h"
   if test -r $PHP_GNUPG/$SEARCH_FOR; then
     GNUPG_DIR=$PHP_GNUPG
