$NetBSD$

--- src/base/platform/platform-posix.cc.orig	2015-01-10 01:24:51.000000000 +0000
+++ src/base/platform/platform-posix.cc
@@ -143,6 +143,9 @@ void OS::Initialize(int64_t random_seed,
   }
   g_hard_abort = hard_abort;
   g_gc_fake_mmap = gc_fake_mmap;
+#ifdef __NetBSD__
+  _LIB_VERSION = _IEEE_;	/* Force IEEE 754 version of libm */
+#endif
 }
 
 
@@ -453,6 +456,10 @@ class Thread::PlatformData {
   Mutex thread_creation_mutex_;
 };
 
+#ifndef PTHREAD_STACK_MIN
+#define PTHREAD_STACK_MIN 16384 /* Somewhat arbitrarily chosen */
+#endif
+
 Thread::Thread(const Options& options)
     : data_(new PlatformData),
       stack_size_(options.stack_size()),
@@ -474,7 +481,7 @@ static void SetThreadName(const char* na
   pthread_set_name_np(pthread_self(), name);
 #elif V8_OS_NETBSD
   STATIC_ASSERT(Thread::kMaxThreadNameLength <= PTHREAD_MAX_NAMELEN_NP);
-  pthread_setname_np(pthread_self(), "%s", name);
+  pthread_setname_np(pthread_self(), "%s", (void*)name);
 #elif V8_OS_MACOSX
   // pthread_setname_np is only available in 10.6 or later, so test
   // for it at runtime.
