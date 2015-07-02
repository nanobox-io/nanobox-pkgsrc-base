$NetBSD$

--- unrar/os.hpp.orig	2012-07-29 13:41:03.000000000 +0000
+++ unrar/os.hpp
@@ -149,7 +149,7 @@
 #if defined(RAR_SMP) && defined(__APPLE__)
   #include <sys/sysctl.h>
 #endif
-#if defined(__FreeBSD__) || defined (__NetBSD__) || defined (__OpenBSD__) || defined(__APPLE__)
+#if defined(__FreeBSD__) || defined (__NetBSD__) || defined (__OpenBSD__) || defined(__APPLE__) || defined(__sun)
   #include <sys/param.h>
   #include <sys/mount.h>
 #else
@@ -226,6 +226,10 @@
     #define LITTLE_ENDIAN
   #elif defined(BYTE_ORDER) && BYTE_ORDER == BIG_ENDIAN
     #define BIG_ENDIAN
+  #elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
+    #define LITTLE_ENDIAN
+  #elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
+    #define BIG_ENDIAN
   #else
     #error "Neither LITTLE_ENDIAN nor BIG_ENDIAN are defined. Define one of them."
   #endif
