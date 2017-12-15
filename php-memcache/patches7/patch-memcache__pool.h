$NetBSD$

--- memcache_pool.h.orig	2013-04-08 02:12:54.000000000 +0000
+++ memcache_pool.h
@@ -42,17 +42,9 @@
 #include <string.h>
 
 #include "php.h"
-#include "ext/standard/php_smart_str_public.h"
+#include "ext/standard/php_smart_string_public.h"
 #include "memcache_queue.h"
 
-#ifndef ZSTR
-#define ZSTR
-#define ZSTR_VAL(v) v
-#define zstr char *
-#else
-#define ZSTR_VAL(v) (v).s
-#endif
-
 /*
  * Mac OS X has no MSG_NOSIGNAL but >= 10.2 comes with SO_NOSIGPIPE which is a setsockopt() option
  * and not a send() parameter as MSG_NOSIGNAL. OpenBSD has none of the options so we need to ignore 
@@ -128,21 +120,30 @@
 
 /* io buffer */
 typedef struct mmc_buffer {
-	smart_str		value;
+	smart_string	value;
 	unsigned int	idx;					/* current index */
 } mmc_buffer_t;
 
-#define mmc_buffer_release(b) memset((b), 0, sizeof(*(b)))
+#define mmc_buffer_release(b) ZEND_SECURE_ZERO((b), sizeof(*(b)))
 #define mmc_buffer_reset(b) (b)->value.len = (b)->idx = 0
 
-inline void mmc_buffer_alloc(mmc_buffer_t *, unsigned int);
-inline void mmc_buffer_free(mmc_buffer_t *);
+#ifdef PHP_WIN32
+#define MMC_POOL_INLINE
+#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
+/* see https://gcc.gnu.org/gcc-5/porting_to.html */
+#define MMC_POOL_INLINE extern inline
+#else
+#define MMC_POOL_INLINE inline
+#endif
+
+void mmc_buffer_alloc(mmc_buffer_t *, unsigned int);
+void mmc_buffer_free(mmc_buffer_t *);
 
 /* stream handlers */
 typedef struct mmc_stream mmc_stream_t;
 
-typedef size_t (*mmc_stream_read)(mmc_stream_t *stream, char *buf, size_t count TSRMLS_DC);
-typedef char *(*mmc_stream_readline)(mmc_stream_t *stream, char *buf, size_t maxlen, size_t *retlen TSRMLS_DC);
+typedef size_t (*mmc_stream_read)(mmc_stream_t *stream, char *buf, size_t count);
+typedef char *(*mmc_stream_readline)(mmc_stream_t *stream, char *buf, size_t maxlen, size_t *retlen);
 
 /* stream container */
 struct mmc_stream {
@@ -167,15 +168,15 @@ typedef struct mmc mmc_t;
 typedef struct mmc_pool mmc_pool_t;
 typedef struct mmc_request mmc_request_t;
 
-typedef int (*mmc_request_reader)(mmc_t *mmc, mmc_request_t *request TSRMLS_DC);
-typedef int (*mmc_request_parser)(mmc_t *mmc, mmc_request_t *request TSRMLS_DC);
+typedef int (*mmc_request_reader)(mmc_t *mmc, mmc_request_t *request);
+typedef int (*mmc_request_parser)(mmc_t *mmc, mmc_request_t *request);
 typedef int (*mmc_request_value_handler)(
 	const char *key, unsigned int key_len, zval *value,
-	unsigned int flags, unsigned long cas, void *param TSRMLS_DC);
+	unsigned int flags, unsigned long cas, void *param);
 typedef int (*mmc_request_response_handler)(
-	mmc_t *mmc, mmc_request_t *request, int response, const char *message, unsigned int message_len, void *param TSRMLS_DC);
+	mmc_t *mmc, mmc_request_t *request, int response, const char *message, unsigned int message_len, void *param);
 typedef int (*mmc_request_failover_handler)(
-	mmc_pool_t *pool, mmc_t *mmc, mmc_request_t *request, void *param TSRMLS_DC);
+	mmc_pool_t *pool, mmc_t *mmc, mmc_request_t *request, void *param);
 
 void mmc_request_reset(mmc_request_t *);
 void mmc_request_free(mmc_request_t *);
@@ -256,7 +257,7 @@ typedef void (*mmc_protocol_end_get)(mmc
 
 typedef int (*mmc_protocol_store)(
 	mmc_pool_t *pool, mmc_request_t *request, int op, const char *key, unsigned int key_len,
-	unsigned int flags, unsigned int exptime, unsigned long cas, zval *value TSRMLS_DC);
+	unsigned int flags, unsigned int exptime, unsigned long cas, zval *value);
 typedef void (*mmc_protocol_delete)(mmc_request_t *request, const char *key, unsigned int key_len, unsigned int exptime);
 typedef void (*mmc_protocol_mutate)(mmc_request_t *request, zval *zkey, const char *key, unsigned int key_len, long value, long defval, int defval_used, unsigned int exptime);
 
@@ -264,6 +265,8 @@ typedef void (*mmc_protocol_flush)(mmc_r
 typedef void (*mmc_protocol_stats)(mmc_request_t *request, const char *type, long slabid, long limit);
 typedef void (*mmc_protocol_version)(mmc_request_t *request);
 
+typedef void (*mmc_protocol_set_sasl_auth_data)(mmc_pool_t *pool, mmc_request_t *request, const char *user, const char *password);
+
 typedef struct mmc_protocol {
 	mmc_protocol_create_request	create_request;
 	mmc_protocol_clone_request	clone_request;
@@ -282,6 +285,8 @@ typedef struct mmc_protocol {
 	mmc_protocol_flush		flush;
 	mmc_protocol_version	version;
 	mmc_protocol_stats		stats;
+	
+	mmc_protocol_set_sasl_auth_data set_sasl_auth_data;
 } mmc_protocol_t;
 
 extern mmc_protocol_t mmc_ascii_protocol;
@@ -305,7 +310,7 @@ extern mmc_hash_function_t mmc_hash_fnv1
 
 typedef void * (*mmc_hash_create_state)(mmc_hash_function_t *);
 typedef void (*mmc_hash_free_state)(void *state);
-typedef mmc_t * (*mmc_hash_find_server)(void *state, const char *key, unsigned int key_len TSRMLS_DC);
+typedef mmc_t * (*mmc_hash_find_server)(void *state, const char *key, unsigned int key_len);
 typedef void (*mmc_hash_add_server)(void *state, mmc_t *mmc, unsigned int weight);
 
 typedef struct mmc_hash_strategy {
@@ -323,7 +328,7 @@ extern mmc_hash_strategy_t mmc_consisten
 #define FNV_32_INIT		0x811c9dc5
 
 /* failure callback prototype */
-typedef void (*mmc_failure_callback)(mmc_pool_t *pool, mmc_t *mmc, void *param TSRMLS_DC);
+typedef void (*mmc_failure_callback)(mmc_pool_t *pool, mmc_t *mmc, zval *param);
 
 /* server pool */
 struct mmc_pool {
@@ -345,54 +350,54 @@ struct mmc_pool {
 	double					min_compress_savings;
 	unsigned int			compress_threshold;
 	mmc_failure_callback	failure_callback;			/* receives notification when a server fails */
-	void					*failure_callback_param;
+	zval					failure_callback_param;
 };
 
 /* server functions */
-mmc_t *mmc_server_new(const char *, int, unsigned short, unsigned short, int, double, int TSRMLS_DC);
-void mmc_server_free(mmc_t * TSRMLS_DC);
-void mmc_server_disconnect(mmc_t *mmc, mmc_stream_t *io TSRMLS_DC);
-int mmc_server_valid(mmc_t * TSRMLS_DC);
-int mmc_server_failure(mmc_t *, mmc_stream_t *, const char *, int TSRMLS_DC);
-int mmc_request_failure(mmc_t *, mmc_stream_t *, const char *, unsigned int, int TSRMLS_DC);
+mmc_t *mmc_server_new(const char *, int, unsigned short, unsigned short, int, double, int);
+void mmc_server_free(mmc_t *);
+void mmc_server_disconnect(mmc_t *mmc, mmc_stream_t *io);
+int mmc_server_valid(mmc_t *);
+int mmc_server_failure(mmc_t *, mmc_stream_t *, const char *, int);
+int mmc_request_failure(mmc_t *, mmc_stream_t *, const char *, unsigned int, int);
 
 /* pool functions */
-mmc_pool_t *mmc_pool_new(TSRMLS_D);
-void mmc_pool_free(mmc_pool_t * TSRMLS_DC);
+mmc_pool_t *mmc_pool_new();
+void mmc_pool_free(mmc_pool_t *);
 void mmc_pool_add(mmc_pool_t *, mmc_t *, unsigned int);
-void mmc_pool_close(mmc_pool_t * TSRMLS_DC);
-int mmc_pool_open(mmc_pool_t *, mmc_t *, mmc_stream_t *, int TSRMLS_DC);
-void mmc_pool_select(mmc_pool_t * TSRMLS_DC);
-void mmc_pool_run(mmc_pool_t * TSRMLS_DC);
-mmc_t *mmc_pool_find_next(mmc_pool_t *, const char *, unsigned int, mmc_queue_t *, unsigned int * TSRMLS_DC);
-mmc_t *mmc_pool_find(mmc_pool_t *, const char *, unsigned int TSRMLS_DC);
-int mmc_pool_schedule(mmc_pool_t *, mmc_t *, mmc_request_t * TSRMLS_DC);
-int mmc_pool_failover_handler(mmc_pool_t *, mmc_t *, mmc_request_t *, void * TSRMLS_DC);
-int mmc_pool_failover_handler_null(mmc_pool_t *, mmc_t *, mmc_request_t *, void * TSRMLS_DC);
+void mmc_pool_close(mmc_pool_t *);
+int mmc_pool_open(mmc_pool_t *, mmc_t *, mmc_stream_t *, int);
+void mmc_pool_select(mmc_pool_t *);
+void mmc_pool_run(mmc_pool_t *);
+mmc_t *mmc_pool_find_next(mmc_pool_t *, const char *, unsigned int, mmc_queue_t *, unsigned int *);
+mmc_t *mmc_pool_find(mmc_pool_t *, const char *, unsigned int);
+int mmc_pool_schedule(mmc_pool_t *, mmc_t *, mmc_request_t *);
+int mmc_pool_failover_handler(mmc_pool_t *, mmc_t *, mmc_request_t *, void *);
+int mmc_pool_failover_handler_null(mmc_pool_t *, mmc_t *, mmc_request_t *, void *);
 
 mmc_request_t *mmc_pool_request(mmc_pool_t *, int,
-	mmc_request_response_handler, void *, mmc_request_failover_handler, void * TSRMLS_DC);
+	mmc_request_response_handler, void *, mmc_request_failover_handler, void *);
 mmc_request_t *mmc_pool_request_get(mmc_pool_t *, int,
-	mmc_request_value_handler, void *, mmc_request_failover_handler, void * TSRMLS_DC);
+	mmc_request_value_handler, void *, mmc_request_failover_handler, void *);
 
 #define mmc_pool_release(p, r) mmc_queue_push(&((p)->free_requests), (r))
 
 int mmc_prepare_store(
 	mmc_pool_t *, mmc_request_t *, const char *, unsigned int,
-	const char *, unsigned int, unsigned int, unsigned int, zval * TSRMLS_DC);
+	const char *, unsigned int, unsigned int, unsigned int, zval *);
 
-int mmc_pool_schedule_key(mmc_pool_t *, const char *, unsigned int, mmc_request_t *, unsigned int TSRMLS_DC);
+int mmc_pool_schedule_key(mmc_pool_t *, const char *, unsigned int, mmc_request_t *, unsigned int);
 int mmc_pool_schedule_get(mmc_pool_t *, int, int, zval *,
-	mmc_request_value_handler, void *, mmc_request_failover_handler, void *, mmc_request_t * TSRMLS_DC);
+	mmc_request_value_handler, void *, mmc_request_failover_handler, void *, mmc_request_t *);
 
 /* utility functions */
-int mmc_pack_value(mmc_pool_t *, mmc_buffer_t *, zval *, unsigned int * TSRMLS_DC);
-int mmc_unpack_value(mmc_t *, mmc_request_t *, mmc_buffer_t *, const char *, unsigned int, unsigned int, unsigned long, unsigned int TSRMLS_DC);
+int mmc_pack_value(mmc_pool_t *, mmc_buffer_t *, zval *, unsigned int *);
+int mmc_unpack_value(mmc_t *, mmc_request_t *, mmc_buffer_t *, const char *, unsigned int, unsigned int, unsigned long, unsigned int);
 double timeval_to_double(struct timeval tv);
 struct timeval double_to_timeval(double sec);
 
-inline int mmc_prepare_key_ex(const char *, unsigned int, char *, unsigned int *);
-inline int mmc_prepare_key(zval *, char *, unsigned int *);
+int mmc_prepare_key_ex(const char *, unsigned int, char *, unsigned int *);
+int mmc_prepare_key(zval *, char *, unsigned int *);
 
 #define mmc_str_left(h, n, hlen, nlen) ((hlen) >= (nlen) ? memcmp((h), (n), (nlen)) == 0 : 0)
 
