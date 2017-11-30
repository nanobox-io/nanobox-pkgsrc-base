$NetBSD$

--- src/mongo/shell/bench.cpp.orig	2017-09-21 03:44:21.000000000 +0000
+++ src/mongo/shell/bench.cpp
@@ -35,6 +35,7 @@
 #include "mongo/shell/bench.h"
 
 #include <pcrecpp.h>
+#include <string>
 #include <iostream>
 
 #include "mongo/client/dbclientcursor.h"
@@ -79,6 +80,7 @@ using std::unique_ptr;
 using std::cout;
 using std::endl;
 using std::map;
+using std::string;
 
 const std::map<OpType, std::string> opTypeName{{OpType::NONE, "none"},
                                                {OpType::NOP, "nop"},
