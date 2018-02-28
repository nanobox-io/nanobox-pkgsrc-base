$NetBSD$

--- src/mongo/db/dbwebserver.cpp.orig	2017-10-18 16:01:51.000000000 +0000
+++ src/mongo/db/dbwebserver.cpp
@@ -35,6 +35,7 @@
 
 #include "mongo/db/dbwebserver.h"
 
+#include <string>
 #include <pcrecpp.h>
 
 #include "mongo/base/init.h"
