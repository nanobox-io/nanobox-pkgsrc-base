$NetBSD$

--- memcache_queue.h.orig	2013-04-08 02:12:54.000000000 +0000
+++ memcache_queue.h
@@ -33,22 +33,25 @@ typedef struct mmc_queue {
 	int		len;
 } mmc_queue_t;
 
-#define mmc_queue_release(q) memset((q), 0, sizeof(*(q)))
+#define mmc_queue_release(q) ZEND_SECURE_ZERO((q), sizeof(*(q)))
 #define mmc_queue_reset(q) (q)->len = (q)->head = (q)->tail = 0
 #define mmc_queue_item(q, i) ((q)->tail + (i) < (q)->alloc ? (q)->items[(q)->tail + (i)] : (q)->items[(i) - ((q)->alloc - (q)->tail)]) 
 
 #ifdef PHP_WIN32
 #define MMC_QUEUE_INLINE
+#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
+/* see https://gcc.gnu.org/gcc-5/porting_to.html */
+#define MMC_QUEUE_INLINE extern inline
 #else
 #define MMC_QUEUE_INLINE inline
 #endif
 
-MMC_QUEUE_INLINE void mmc_queue_push(mmc_queue_t *, void *);
-MMC_QUEUE_INLINE void *mmc_queue_pop(mmc_queue_t *);
-MMC_QUEUE_INLINE int mmc_queue_contains(mmc_queue_t *, void *);
-MMC_QUEUE_INLINE void mmc_queue_free(mmc_queue_t *);
-MMC_QUEUE_INLINE void mmc_queue_copy(mmc_queue_t *, mmc_queue_t *);
-MMC_QUEUE_INLINE void mmc_queue_remove(mmc_queue_t *, void *);
+void mmc_queue_push(mmc_queue_t *, void *);
+void *mmc_queue_pop(mmc_queue_t *);
+int mmc_queue_contains(mmc_queue_t *, void *);
+void mmc_queue_free(mmc_queue_t *);
+void mmc_queue_copy(mmc_queue_t *, mmc_queue_t *);
+void mmc_queue_remove(mmc_queue_t *, void *);
 
 #endif /*MEMCACHE_QUEUE_H_*/
 
