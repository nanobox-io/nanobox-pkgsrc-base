$NetBSD$

--- sql/mysqld.h.orig	2014-06-09 17:45:44.536906677 +0000
+++ sql/mysqld.h
@@ -483,6 +483,8 @@ extern "C" void unireg_clear(int exit_co
 #define unireg_abort(exit_code) do { unireg_clear(exit_code); DBUG_RETURN(exit_code); } while(0)
 #endif
 
+int unireg_abort_no_return(int exit_code);
+
 inline void table_case_convert(char * name, uint length)
 {
   if (lower_case_table_names)
