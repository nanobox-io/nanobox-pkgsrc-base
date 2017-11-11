$NetBSD$

--- deps/v8/src/base/platform/semaphore.cc.orig	2016-10-25 13:26:03.000000000 +0000
+++ deps/v8/src/base/platform/semaphore.cc
@@ -11,6 +11,10 @@
 
 #include <errno.h>
 
+#if V8_OS_NETBSD
+#include <sys/param.h>	// for __NetBSD_Version__
+#endif
+
 #include "src/base/logging.h"
 #include "src/base/platform/elapsed-timer.h"
 #include "src/base/platform/time.h"
