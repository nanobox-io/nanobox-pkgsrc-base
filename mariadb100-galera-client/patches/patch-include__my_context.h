$NetBSD$

--- include/my_context.h.orig	2014-04-26 22:18:59.000000000 +0000
+++ include/my_context.h
@@ -25,17 +25,7 @@
   (This particular implementation uses Posix ucontext swapcontext().)
 */
 
-#ifdef __WIN__
-#define MY_CONTEXT_USE_WIN32_FIBERS 1
-#elif defined(__GNUC__) && __GNUC__ >= 3 && defined(__x86_64__) && !defined(__ILP32__)
-#define MY_CONTEXT_USE_X86_64_GCC_ASM
-#elif defined(__GNUC__) && __GNUC__ >= 3 && defined(__i386__)
-#define MY_CONTEXT_USE_I386_GCC_ASM
-#elif defined(HAVE_UCONTEXT)
 #define MY_CONTEXT_USE_UCONTEXT
-#else
-#define MY_CONTEXT_DISABLE
-#endif
 
 #ifdef MY_CONTEXT_USE_WIN32_FIBERS
 struct my_context {
