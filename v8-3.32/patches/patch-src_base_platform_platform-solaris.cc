$NetBSD$

--- src/base/platform/platform-solaris.cc.orig	2015-01-10 01:24:51.000000000 +0000
+++ src/base/platform/platform-solaris.cc
@@ -9,6 +9,7 @@
 # error "V8 does not support the SPARC CPU architecture."
 #endif
 
+#include <alloca.h>
 #include <dlfcn.h>  // dladdr
 #include <errno.h>
 #include <ieeefp.h>  // finite()
