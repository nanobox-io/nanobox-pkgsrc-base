$NetBSD$

--- src/pl/plperl/plperl.h.orig	2018-02-05 21:08:57.000000000 +0000
+++ src/pl/plperl/plperl.h
@@ -44,6 +44,11 @@
 #undef vsnprintf
 #endif
 
+#ifdef __sun
+#define list_head sun_list_head
+#define list_tail sun_list_tail
+#endif
+
 /*
  * ActivePerl 5.18 and later are MinGW-built, and their headers use GCC's
  * __inline__.  Translate to something MSVC recognizes.
@@ -70,6 +75,11 @@
 #include "XSUB.h"
 #endif
 
+#ifdef __sun
+#undef list_head
+#undef list_tail
+#endif
+
 /* put back our snprintf and vsnprintf */
 #ifdef USE_REPL_SNPRINTF
 #ifdef snprintf
