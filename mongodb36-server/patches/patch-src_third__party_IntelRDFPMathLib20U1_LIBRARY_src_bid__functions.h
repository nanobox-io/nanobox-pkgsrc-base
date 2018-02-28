$NetBSD$

--- src/third_party/IntelRDFPMathLib20U1/LIBRARY/src/bid_functions.h.orig	2018-01-04 23:28:55.000000000 +0000
+++ src/third_party/IntelRDFPMathLib20U1/LIBRARY/src/bid_functions.h
@@ -159,7 +159,7 @@ typedef unsigned    long fexcept_t;
 typedef unsigned bid__int64 fexcept_t;
 #endif
 #else
-#if defined(__QNX__) || defined(__OpenBSD__)
+#if defined(__QNX__) || defined(__NetBSD__) || defined(__OpenBSD__)
 #include <fenv.h>
 #else
 typedef unsigned short int fexcept_t;
