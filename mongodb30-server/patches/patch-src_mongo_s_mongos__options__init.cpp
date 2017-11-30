$NetBSD$

--- src/mongo/s/mongos_options_init.cpp.orig	2017-05-01 20:06:54.000000000 +0000
+++ src/mongo/s/mongos_options_init.cpp
@@ -28,6 +28,8 @@
 
 #include "mongo/s/mongos_options.h"
 
+#include <iostream>
+
 #include "mongo/util/options_parser/startup_option_init.h"
 #include "mongo/util/options_parser/startup_options.h"
 #include "mongo/util/quick_exit.h"
