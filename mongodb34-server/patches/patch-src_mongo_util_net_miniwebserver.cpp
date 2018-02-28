$NetBSD$

--- src/mongo/util/net/miniwebserver.cpp.orig	2017-10-18 16:01:51.000000000 +0000
+++ src/mongo/util/net/miniwebserver.cpp
@@ -33,6 +33,7 @@
 
 #include "mongo/util/net/miniwebserver.h"
 
+#include <string>
 #include <pcrecpp.h>
 
 #include "mongo/config.h"
