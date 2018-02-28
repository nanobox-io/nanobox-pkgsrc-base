$NetBSD$

--- src/mongo/util/net/miniwebserver.cpp.orig	2017-11-20 23:56:23.000000000 +0000
+++ src/mongo/util/net/miniwebserver.cpp
@@ -33,6 +33,7 @@
 
 #include "mongo/util/net/miniwebserver.h"
 
+#include <string>
 #include <pcrecpp.h>
 
 #include "mongo/config.h"
