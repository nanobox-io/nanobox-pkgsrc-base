$NetBSD$

--- ext/tidy/tidy.c.orig	2015-09-01 20:09:37.000000000 +0000
+++ ext/tidy/tidy.c
@@ -31,7 +31,7 @@
 #include "ext/standard/info.h"
 
 #include "tidy.h"
-#include "buffio.h"
+#include "tidybuffio.h"
 
 /* compatibility with older versions of libtidy */
 #ifndef TIDY_CALL
