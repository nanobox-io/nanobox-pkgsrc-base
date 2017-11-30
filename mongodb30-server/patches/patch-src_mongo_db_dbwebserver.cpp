$NetBSD$

--- src/mongo/db/dbwebserver.cpp.orig	2017-05-01 20:06:54.000000000 +0000
+++ src/mongo/db/dbwebserver.cpp
@@ -37,6 +37,7 @@
 
 #include <boost/date_time/posix_time/posix_time.hpp>
 #include <pcrecpp.h>
+#include <string>
 
 #include "mongo/base/init.h"
 #include "mongo/db/auth/authorization_manager.h"
@@ -62,6 +63,7 @@
 namespace mongo {
 
 using std::map;
+using std::string;
 using std::stringstream;
 using std::vector;
 
