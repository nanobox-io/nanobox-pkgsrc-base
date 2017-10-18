$NetBSD$

--- memcache_pool.h.orig	2013-04-08 02:12:54.000000000 +0000
+++ memcache_pool.h
@@ -42,7 +42,7 @@
 #include <string.h>
 
 #include "php.h"
-#include "ext/standard/php_smart_str_public.h"
+#include "ext/standard/php_smart_string_public.h"
 #include "memcache_queue.h"
 
 #ifndef ZSTR
