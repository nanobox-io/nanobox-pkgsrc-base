$NetBSD$

--- src/mongo/db/dbwebserver.cpp.orig	2017-09-21 03:44:21.000000000 +0000
+++ src/mongo/db/dbwebserver.cpp
@@ -36,6 +36,7 @@
 #include "mongo/db/dbwebserver.h"
 
 #include <boost/date_time/posix_time/posix_time.hpp>
+#include <string>
 #include <pcrecpp.h>
 
 #include "mongo/base/init.h"
@@ -69,6 +70,7 @@ namespace mongo {
 using std::map;
 using std::stringstream;
 using std::vector;
+using std::string;
 
 using namespace html;
 
