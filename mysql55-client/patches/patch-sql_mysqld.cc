$NetBSD$

--- sql/mysqld.cc.orig	2014-06-09 18:56:02.564588335 +0000
+++ sql/mysqld.cc
@@ -167,7 +167,7 @@ extern int memcntl(caddr_t, size_t, int,
 int initgroups(const char *,unsigned int);
 #endif
 
-#if defined(__FreeBSD__) && defined(HAVE_IEEEFP_H) && !defined(HAVE_FEDISABLEEXCEPT)
+#if (defined(__FreeBSD__) || defined(__DragonFly__)) && defined(HAVE_IEEEFP_H) && !defined(HAVE_FEDISABLEEXCEPT)
 #include <ieeefp.h>
 #ifdef HAVE_FP_EXCEPT				// Fix type conflict
 typedef fp_except fp_except_t;
@@ -198,7 +198,7 @@ extern "C" my_bool reopen_fstreams(const
 
 inline void setup_fpu()
 {
-#if defined(__FreeBSD__) && defined(HAVE_IEEEFP_H) && !defined(HAVE_FEDISABLEEXCEPT)
+#if (defined(__FreeBSD__) || defined(__DragonFly__)) && defined(HAVE_IEEEFP_H) && !defined(HAVE_FEDISABLEEXCEPT)
   /* We can't handle floating point exceptions with threads, so disable
      this on freebsd
      Don't fall for overflow, underflow,divide-by-zero or loss of precision.
@@ -4825,9 +4825,15 @@ void wsrep_kill_mysql(THD *thd)
   }
   else
   {
-    unireg_abort(1);
+    unireg_abort_no_return(1);
   }
 }
+
+int unireg_abort_no_return(int exit_code)
+{
+  unireg_abort(exit_code);
+}
+
 #endif /* WITH_WSREP */
 
 #if (defined(_WIN32) || defined(HAVE_SMEM)) && !defined(EMBEDDED_LIBRARY)
