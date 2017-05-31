$NetBSD$

--- vm_eval.c.orig	2016-12-27 10:49:55.000000000 +0000
+++ vm_eval.c
@@ -1111,7 +1111,7 @@ rb_iterate(VALUE (* it_proc) (VALUE), VA
     int state;
     volatile VALUE retval = Qnil;
     NODE *node = NEW_IFUNC(bl_proc, data2);
-    rb_thread_t *th = GET_THREAD();
+    rb_thread_t * volatile th = GET_THREAD();
     rb_control_frame_t *volatile cfp = th->cfp;
 
     node->nd_aid = rb_frame_this_func();
@@ -1983,7 +1983,7 @@ rb_catch_protect(VALUE t, rb_block_call_
 {
     int state;
     volatile VALUE val = Qnil;		/* OK */
-    rb_thread_t *th = GET_THREAD();
+    rb_thread_t * volatile th = GET_THREAD();
     rb_control_frame_t *volatile saved_cfp = th->cfp;
     volatile VALUE tag = t;
 
