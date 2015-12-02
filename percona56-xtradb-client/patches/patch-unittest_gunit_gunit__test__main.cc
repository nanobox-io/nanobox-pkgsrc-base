$NetBSD$

--- unittest/gunit/gunit_test_main.cc.orig	2015-10-13 12:15:42.000000000 +0000
+++ unittest/gunit/gunit_test_main.cc
@@ -57,6 +57,47 @@ mysql_mutex_t LOCK_open;
 uint    opt_debug_sync_timeout= 0;
 pthread_key(MEM_ROOT**,THR_MALLOC);
 pthread_key(THD*, THR_THD);
+#include "wsrep_mysqld.h"
+#include "sql_class.h"
+my_bool wsrep_log_conflicts= 0;
+my_bool wsrep_debug= 0;
+extern "C" char *wsrep_thd_query(THD *thd)
+{
+  return (thd) ? thd->query() : NULL;
+}
+
+extern "C" my_thread_id wsrep_thd_thread_id(THD *thd)
+{
+  return thd->thread_id;
+}
+
+void sql_print_information(const char *format, ...)
+{
+  va_list args;
+
+  va_start(args, format);
+  //error_log_print(INFORMATION_LEVEL, format, args);
+  va_end(args);
+}
+
+my_bool wsrep_thd_is_BF(void *thd_ptr, my_bool sync)
+{
+  my_bool status = FALSE;
+  if (thd_ptr)
+  {
+    //THD* thd = (THD*)thd_ptr;
+    //if (sync) mysql_mutex_lock(&thd->LOCK_wsrep_thd);
+    status = TRUE; 
+    //if (sync) mysql_mutex_unlock(&thd->LOCK_wsrep_thd);
+  }
+  return status;
+}
+
+bool wsrep_grant_mdl_exception(MDL_context *requestor_ctx,
+                          MDL_ticket *ticket
+) {
+  return TRUE;
+}
 
 extern "C" void sql_alloc_error_handler(void)
 {
