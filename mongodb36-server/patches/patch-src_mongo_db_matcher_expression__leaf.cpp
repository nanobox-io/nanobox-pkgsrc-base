$NetBSD$

--- src/mongo/db/matcher/expression_leaf.cpp.orig	2018-02-16 21:50:58.000000000 +0000
+++ src/mongo/db/matcher/expression_leaf.cpp
@@ -31,6 +31,7 @@
 #include "mongo/db/matcher/expression_leaf.h"
 
 #include <cmath>
+#include <string>
 #include <pcrecpp.h>
 
 #include "mongo/bson/bsonelement_comparator.h"
@@ -46,6 +47,7 @@
 #include "mongo/util/mongoutils/str.h"
 
 namespace mongo {
+using std::string;
 
 bool ComparisonMatchExpressionBase::equivalent(const MatchExpression* other) const {
     if (other->matchType() != matchType())
