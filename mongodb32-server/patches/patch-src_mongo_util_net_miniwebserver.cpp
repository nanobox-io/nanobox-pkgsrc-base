$NetBSD$

--- src/mongo/util/net/miniwebserver.cpp.orig	2017-09-21 03:44:21.000000000 +0000
+++ src/mongo/util/net/miniwebserver.cpp
@@ -33,6 +33,7 @@
 
 #include "mongo/util/net/miniwebserver.h"
 
+#include <string>
 #include <pcrecpp.h>
 
 #include "mongo/config.h"
@@ -42,6 +43,7 @@
 namespace mongo {
 
 using std::shared_ptr;
+using std::string;
 using std::endl;
 using std::stringstream;
 using std::vector;
