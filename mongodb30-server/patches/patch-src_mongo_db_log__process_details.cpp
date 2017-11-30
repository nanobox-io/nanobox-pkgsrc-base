$NetBSD$

--- src/mongo/db/log_process_details.cpp.orig	2017-05-01 20:06:54.000000000 +0000
+++ src/mongo/db/log_process_details.cpp
@@ -30,6 +30,8 @@
 
 #define MONGO_LOG_DEFAULT_COMPONENT ::mongo::logger::LogComponent::kControl
 
+#include <iostream>
+
 #include "mongo/platform/basic.h"
 
 #include "mongo/db/log_process_details.h"
