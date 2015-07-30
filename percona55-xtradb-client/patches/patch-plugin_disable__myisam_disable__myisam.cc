$NetBSD$

--- plugin/disable_myisam/disable_myisam.cc.orig	2015-07-28 00:20:42.366213691 +0000
+++ plugin/disable_myisam/disable_myisam.cc
@@ -20,6 +20,8 @@
 #include "handler.h"
 #include "sql_plugin.h"                         // st_plugin_int
 #include "log.h"
+#undef max
+#undef min
 #include <set>
 //#include "sp.h"
 //#include "table_cache.h"
