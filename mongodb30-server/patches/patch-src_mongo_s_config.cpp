$NetBSD$

--- src/mongo/s/config.cpp.orig	2017-05-01 20:06:54.000000000 +0000
+++ src/mongo/s/config.cpp
@@ -34,6 +34,7 @@
 
 #include <boost/scoped_ptr.hpp>
 #include "pcrecpp.h"
+#include <string>
 
 #include "mongo/client/connpool.h"
 #include "mongo/client/dbclientcursor.h"
@@ -64,6 +65,7 @@ namespace mongo {
 
 using boost::scoped_ptr;
 using std::auto_ptr;
+using std::string;
 using std::endl;
 using std::pair;
 using std::set;
