$NetBSD$

--- ext/tidy/tidy.c.orig	2014-08-13 19:22:50.000000000 +0000
+++ ext/tidy/tidy.c
@@ -32,7 +32,7 @@
 #include "safe_mode.h"
 
 #include "tidy.h"
-#include "buffio.h"
+#include "tidybuffio.h"
 
 /* compatibility with older versions of libtidy */
 #ifndef TIDY_CALL
