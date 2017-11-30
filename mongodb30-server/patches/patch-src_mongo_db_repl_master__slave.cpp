$NetBSD$

--- src/mongo/db/repl/master_slave.cpp.orig	2017-05-01 20:06:54.000000000 +0000
+++ src/mongo/db/repl/master_slave.cpp
@@ -45,6 +45,7 @@
 #include "mongo/db/repl/master_slave.h"
 
 #include <iostream>
+#include <string>
 #include <pcrecpp.h>
 #include <boost/scoped_ptr.hpp>
 #include <boost/shared_ptr.hpp>
@@ -73,6 +74,7 @@
 using boost::scoped_ptr;
 using std::auto_ptr;
 using std::cout;
+using std::string;
 using std::endl;
 using std::max;
 using std::min;
