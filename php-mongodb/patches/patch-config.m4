$NetBSD$

--- config.m4.orig	2015-05-06 16:48:56.000000000 +0000
+++ config.m4
@@ -354,7 +354,7 @@ PHP_ARG_WITH(mongodb-sasl, Build with Cy
 
 if test "$PHP_MONGODB_SASL" != "no"; then
   AC_MSG_CHECKING(for SASL)
-  for i in $MONGODB_SASL /usr /usr/local; do
+  for i in $MONGODB_SASL /usr /usr/local @PREFIX@; do
     if test -f $i/include/sasl/sasl.h; then
       MONGODB_SASL_DIR=$i
       AC_MSG_RESULT(found in $i)
