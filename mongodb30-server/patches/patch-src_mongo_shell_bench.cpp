$NetBSD$

--- src/mongo/shell/bench.cpp.orig	2017-05-01 20:06:54.000000000 +0000
+++ src/mongo/shell/bench.cpp
@@ -39,6 +39,7 @@
 #include <boost/noncopyable.hpp>
 #include <boost/shared_ptr.hpp>
 #include <boost/thread/thread.hpp>
+#include <string>
 #include <iostream>
 
 #include "mongo/db/namespace_string.h"
@@ -80,6 +81,7 @@ using std::auto_ptr;
 using std::cout;
 using std::endl;
 using std::map;
+using std::string;
 
 BenchRunEventCounter::BenchRunEventCounter() {
     reset();
