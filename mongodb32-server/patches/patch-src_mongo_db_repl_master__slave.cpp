$NetBSD$

--- src/mongo/db/repl/master_slave.cpp.orig	2017-09-21 03:44:21.000000000 +0000
+++ src/mongo/db/repl/master_slave.cpp
@@ -45,6 +45,7 @@
 #include "mongo/db/repl/master_slave.h"
 
 #include <pcrecpp.h>
+#include <string>
 
 #include "mongo/db/auth/authorization_manager.h"
 #include "mongo/db/auth/authorization_session.h"
@@ -77,6 +78,7 @@ using std::endl;
 using std::max;
 using std::min;
 using std::set;
+using std::string;
 using std::stringstream;
 using std::unique_ptr;
 using std::vector;
