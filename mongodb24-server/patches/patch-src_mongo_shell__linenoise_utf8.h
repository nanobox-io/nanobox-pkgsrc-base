$NetBSD$

--- src/mongo/shell/linenoise_utf8.h.orig	2015-04-27 16:18:57.000000000 +0000
+++ src/mongo/shell/linenoise_utf8.h
@@ -17,6 +17,7 @@
 
 #include <boost/smart_ptr/scoped_array.hpp>
 #include <string.h>
+#include <algorithm>
 
 namespace linenoise_utf8 {
 
