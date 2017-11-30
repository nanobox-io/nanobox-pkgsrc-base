$NetBSD$

--- src/mongo/util/net/miniwebserver.cpp.orig	2017-05-01 20:06:54.000000000 +0000
+++ src/mongo/util/net/miniwebserver.cpp
@@ -35,6 +35,7 @@
 
 #include <boost/shared_ptr.hpp>
 #include <pcrecpp.h>
+#include <string>
 
 #include "mongo/util/hex.h"
 #include "mongo/util/log.h"
@@ -42,6 +43,7 @@
 namespace mongo {
 
 using boost::shared_ptr;
+using std::string;
 using std::endl;
 using std::stringstream;
 using std::vector;
