$NetBSD$

--- src/third_party/IntelRDFPMathLib20U1/LIBRARY/float128/dpml_exception.c.orig	2018-01-04 23:28:55.000000000 +0000
+++ src/third_party/IntelRDFPMathLib20U1/LIBRARY/float128/dpml_exception.c
@@ -132,6 +132,7 @@
     !defined(wnt)
 
 #   include <signal.h>
+#   include <sys/types.h>
 #   include <sys/signal.h>
 #   define DPML_SIGNAL(p)	 raise(SIGFPE)
 
