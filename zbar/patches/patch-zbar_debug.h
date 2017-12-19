$NetBSD$

--- zbar/debug.h.orig	2009-10-23 18:16:44.000000000 +0000
+++ zbar/debug.h
@@ -27,10 +27,10 @@
 
 # ifdef __GNUC__
     /* older versions of gcc (< 2.95) require a named varargs parameter */
-#  define dprintf(args...)
+#  define zbar_dprintf(args...)
 # else
     /* unfortunately named vararg parameter is a gcc-specific extension */
-#  define dprintf(...)
+#  define zbar_dprintf(...)
 # endif
 
 #else
@@ -38,11 +38,11 @@
 # include <stdio.h>
 
 # ifdef __GNUC__
-#  define dprintf(level, args...) \
+#  define zbar_dprintf(level, args...) \
     if((level) <= DEBUG_LEVEL)    \
         fprintf(stderr, args)
 # else
-#  define dprintf(level, ...)     \
+#  define zbar_dprintf(level, ...)     \
     if((level) <= DEBUG_LEVEL)    \
         fprintf(stderr, __VA_ARGS__)
 # endif
