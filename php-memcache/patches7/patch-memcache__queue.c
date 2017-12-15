$NetBSD$

--- memcache_queue.c.orig	2013-04-08 02:12:54.000000000 +0000
+++ memcache_queue.c
@@ -91,7 +91,7 @@ MMC_QUEUE_INLINE void mmc_queue_free(mmc
 	if (queue->items != NULL) {
 		efree(queue->items);
 	}
-	memset(queue, 0, sizeof(*queue));
+	ZEND_SECURE_ZERO(queue, sizeof(*queue));
 }
 
 MMC_QUEUE_INLINE void mmc_queue_copy(mmc_queue_t *target, mmc_queue_t *source) {
