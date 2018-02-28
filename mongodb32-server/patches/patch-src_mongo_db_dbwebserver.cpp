$NetBSD$

--- src/mongo/db/dbwebserver.cpp.orig	2017-11-20 23:56:23.000000000 +0000
+++ src/mongo/db/dbwebserver.cpp
@@ -36,6 +36,7 @@
 #include "mongo/db/dbwebserver.h"
 
 #include <boost/date_time/posix_time/posix_time.hpp>
+#include <string>
 #include <pcrecpp.h>
 
 #include "mongo/base/init.h"
