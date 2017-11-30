$NetBSD$

--- src/mongo/s/grid.cpp.orig	2017-05-01 20:06:54.000000000 +0000
+++ src/mongo/s/grid.cpp
@@ -36,6 +36,7 @@
 
 #include "pcrecpp.h"
 #include <iomanip>
+#include <string>
 
 #include "mongo/client/connpool.h"
 #include "mongo/client/replica_set_monitor.h"
@@ -58,6 +59,7 @@
 namespace mongo {
 
 using std::endl;
+using std::string;
 using std::istringstream;
 using std::map;
 using std::ostringstream;
