$NetBSD$

--- src/mongo/db/matcher/expression_leaf.cpp.orig	2017-09-21 03:44:21.000000000 +0000
+++ src/mongo/db/matcher/expression_leaf.cpp
@@ -31,6 +31,7 @@
 #include "mongo/db/matcher/expression_leaf.h"
 
 #include <cmath>
+#include <string>
 #include <unordered_map>
 #include <pcrecpp.h>
 
@@ -44,6 +45,7 @@
 #include "mongo/util/mongoutils/str.h"
 
 namespace mongo {
+using std::string;
 
 Status LeafMatchExpression::initPath(StringData path) {
     _path = path;
