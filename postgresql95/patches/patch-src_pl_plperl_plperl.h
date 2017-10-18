$NetBSD$

--- src/pl/plperl/plperl.h.orig	2017-08-07 21:13:41.000000000 +0000
+++ src/pl/plperl/plperl.h
@@ -42,6 +42,10 @@
 #undef vsnprintf
 #endif
 
+#ifdef __sun
+#define list_head sun_list_head
+#define list_tail sun_list_tail
+#endif
 
 /*
  * Get the basic Perl API.  We use PERL_NO_GET_CONTEXT mode so that our code
@@ -60,6 +64,11 @@
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
