$NetBSD$

--- src/mongo/db/matcher/expression_leaf.cpp.orig	2017-05-01 20:06:54.000000000 +0000
+++ src/mongo/db/matcher/expression_leaf.cpp
@@ -31,6 +31,7 @@
 #include "mongo/db/matcher/expression_leaf.h"
 
 #include <pcrecpp.h>
+#include <string>
 
 #include "mongo/bson/bsonobjiterator.h"
 #include "mongo/bson/bsonobj.h"
@@ -40,6 +41,7 @@
 #include "mongo/db/matcher/path.h"
 
 namespace mongo {
+using std::string;
 
 Status LeafMatchExpression::initPath(const StringData& path) {
     _path = path;
