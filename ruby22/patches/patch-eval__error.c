$NetBSD$

--- eval_error.c.orig	2016-12-27 10:49:55.000000000 +0000
+++ eval_error.c
@@ -63,8 +63,8 @@ static void
 error_print(void)
 {
     volatile VALUE errat = Qundef;
-    rb_thread_t *th = GET_THREAD();
-    VALUE errinfo = th->errinfo;
+    rb_thread_t volatile *th = GET_THREAD();
+    volatile VALUE errinfo = th->errinfo;
     volatile int raised_flag = th->raised_flag;
     volatile VALUE eclass = Qundef, e = Qundef;
     const char *volatile einfo;
