$NetBSD$

--- memcache_queue.h.orig	2013-04-08 02:12:54.000000000 +0000
+++ memcache_queue.h
@@ -40,7 +40,7 @@ typedef struct mmc_queue {
 #ifdef PHP_WIN32
 #define MMC_QUEUE_INLINE
 #else
-#define MMC_QUEUE_INLINE inline
+#define MMC_QUEUE_INLINE extern inline
 #endif
 
 MMC_QUEUE_INLINE void mmc_queue_push(mmc_queue_t *, void *);
