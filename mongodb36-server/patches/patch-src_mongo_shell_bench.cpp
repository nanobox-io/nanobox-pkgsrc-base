$NetBSD$

--- src/mongo/shell/bench.cpp.orig	2018-01-04 23:28:55.000000000 +0000
+++ src/mongo/shell/bench.cpp
@@ -32,6 +32,7 @@
 
 #include "mongo/shell/bench.h"
 
+#include <string>
 #include <pcrecpp.h>
 
 #include "mongo/client/dbclientcursor.h"
@@ -50,6 +51,7 @@
 
 namespace mongo {
 namespace {
+using std::string;
 
 const std::map<OpType, std::string> kOpTypeNames{{OpType::NONE, "none"},
                                                  {OpType::NOP, "nop"},
