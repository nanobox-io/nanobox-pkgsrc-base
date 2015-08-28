$NetBSD$

--- ext/openssl/ruby_missing.h.orig	2014-01-30 03:49:07.000000000 +0000
+++ ext/openssl/ruby_missing.h
@@ -25,14 +25,6 @@
 #define rb_io_t OpenFile
 #endif
 
-#ifndef HAVE_RB_STR_SET_LEN
-/* these methods should probably be backported to 1.8 */
-#define rb_str_set_len(str, length) do {	\
-	RSTRING(str)->ptr[(length)] = 0;		\
-	RSTRING(str)->len = (length);		\
-} while(0)
-#endif /* ! HAVE_RB_STR_SET_LEN */
-
 #ifndef HAVE_RB_BLOCK_CALL
 /* the openssl module doesn't use arg[3-4] and arg2 is always rb_each */
 #define rb_block_call(arg1, arg2, arg3, arg4, arg5, arg6) rb_iterate(rb_each, (arg1), (arg5), (arg6))
