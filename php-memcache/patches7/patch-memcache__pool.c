$NetBSD$

--- memcache_pool.c.orig	2013-04-08 02:12:54.000000000 +0000
+++ memcache_pool.c
@@ -35,25 +35,26 @@
 #include "ext/standard/crc32.h"
 #include "ext/standard/php_var.h"
 #include "ext/standard/php_string.h"
-#include "ext/standard/php_smart_str.h"
+#include "ext/standard/php_smart_string.h"
+#include "zend_smart_str.h"
 #include "memcache_pool.h"
 
 ZEND_DECLARE_MODULE_GLOBALS(memcache)
 
-inline void mmc_buffer_alloc(mmc_buffer_t *buffer, unsigned int size)  /*
+MMC_POOL_INLINE void mmc_buffer_alloc(mmc_buffer_t *buffer, unsigned int size)  /*
 	ensures space for an additional size bytes {{{ */
 {
 	register size_t newlen;
-	smart_str_alloc((&(buffer->value)), size, 0);
+	smart_string_alloc((&(buffer->value)), size, 0);
 }
 /* }}} */
 
-inline void mmc_buffer_free(mmc_buffer_t *buffer)  /* {{{ */
+MMC_POOL_INLINE void mmc_buffer_free(mmc_buffer_t *buffer)  /* {{{ */
 {
 	if (buffer->value.c != NULL) {
-		smart_str_free(&(buffer->value));
+		smart_string_free(&(buffer->value));
 	}
-	memset(buffer, 0, sizeof(*buffer));
+	ZEND_SECURE_ZERO(buffer, sizeof(*buffer));
 }
 /* }}} */
 
@@ -85,9 +86,9 @@ static unsigned int mmc_hash_fnv1a_combi
 	while (p < end) {
 		seed ^= (unsigned int)*(p++);
 		seed *= FNV_32_PRIME;
-    }
+	}
 
-    return seed;
+	return seed;
 }
 /* }}} */
 
@@ -111,7 +112,7 @@ struct timeval double_to_timeval(double
 	return tv;
 }
 
-static size_t mmc_stream_read_buffered(mmc_stream_t *io, char *buf, size_t count TSRMLS_DC) /*
+static size_t mmc_stream_read_buffered(mmc_stream_t *io, char *buf, size_t count) /*
 	attempts to reads count bytes from the stream buffer {{{ */
 {
 	size_t toread = io->buffer.value.len - io->buffer.idx < count ? io->buffer.value.len - io->buffer.idx : count;
@@ -121,7 +122,7 @@ static size_t mmc_stream_read_buffered(m
 }
 /* }}} */
 
-static char *mmc_stream_readline_buffered(mmc_stream_t *io, char *buf, size_t maxlen, size_t *retlen TSRMLS_DC)  /*
+static char *mmc_stream_readline_buffered(mmc_stream_t *io, char *buf, size_t maxlen, size_t *retlen)  /*
 	reads count bytes from the stream buffer, this implementation only detects \r\n (like memcached sends) {{{ */
 {
 	char *eol;
@@ -147,15 +148,15 @@ static char *mmc_stream_readline_buffere
 }
 /* }}} */
 
-static size_t mmc_stream_read_wrapper(mmc_stream_t *io, char *buf, size_t count TSRMLS_DC)  /* {{{ */
+static size_t mmc_stream_read_wrapper(mmc_stream_t *io, char *buf, size_t count)  /* {{{ */
 {
 	return php_stream_read(io->stream, buf, count);
 }
 /* }}} */
 
-static char *mmc_stream_readline_wrapper(mmc_stream_t *io, char *buf, size_t maxlen, size_t *retlen TSRMLS_DC)  /* {{{ */
+static char *mmc_stream_readline_wrapper(mmc_stream_t *io, char *buf, size_t maxlen, size_t *retlen)  /* {{{ */
 {
-	return php_stream_get_line(io->stream, ZSTR(buf), maxlen, retlen);
+	return php_stream_get_line(io->stream, buf, maxlen, retlen);
 }
 /* }}} */
 
@@ -177,7 +178,7 @@ void mmc_request_free(mmc_request_t *req
 }
 /* }}} */
 
-static inline int mmc_request_send(mmc_t *mmc, mmc_request_t *request TSRMLS_DC) /* {{{ */
+static inline int mmc_request_send(mmc_t *mmc, mmc_request_t *request) /* {{{ */
 {
 	int count, bytes;
 
@@ -207,12 +208,12 @@ static inline int mmc_request_send(mmc_t
 		}
 
 		message = php_socket_strerror(err, buf, 1024);
-		return mmc_server_failure(mmc, request->io, message, err TSRMLS_CC);
+		return mmc_server_failure(mmc, request->io, message, err);
 	}
 }
 /* }}} */
 
-static int mmc_request_read_udp(mmc_t *mmc, mmc_request_t *request TSRMLS_DC) /*
+static int mmc_request_read_udp(mmc_t *mmc, mmc_request_t *request) /*
 	reads an entire datagram into buffer and validates the udp header {{{ */
 {
 	size_t bytes;
@@ -229,10 +230,10 @@ static int mmc_request_read_udp(mmc_t *m
 	bytes = php_stream_read(request->io->stream, request->io->buffer.value.c + request->io->buffer.value.len, MMC_MAX_UDP_LEN + 1);
 
 	if (bytes < sizeof(mmc_udp_header_t)) {
-		return mmc_server_failure(mmc, request->io, "Failed te read complete UDP header from stream", 0 TSRMLS_CC);
+		return mmc_server_failure(mmc, request->io, "Failed te read complete UDP header from stream", 0);
 	}
 	if (bytes > MMC_MAX_UDP_LEN) {
-		return mmc_server_failure(mmc, request->io, "Server sent packet larger than MMC_MAX_UDP_LEN bytes", 0 TSRMLS_CC);
+		return mmc_server_failure(mmc, request->io, "Server sent packet larger than MMC_MAX_UDP_LEN bytes", 0);
 	}
 
 	header = (mmc_udp_header_t *)(request->io->buffer.value.c + request->io->buffer.value.len);
@@ -256,7 +257,7 @@ static int mmc_request_read_udp(mmc_t *m
 			return MMC_REQUEST_MORE;
 		}
 
-		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "UDP packet loss, expected reqid/seqid %d/%d got %d/%d",
+		php_error_docref(NULL, E_NOTICE, "UDP packet loss, expected reqid/seqid %d/%d got %d/%d",
 			(int)request->udp.reqid, (int)request->udp.seqid, (int)reqid, (int)seqid);
 		return MMC_REQUEST_RETRY;
 	}
@@ -279,7 +280,7 @@ static int mmc_request_read_udp(mmc_t *m
 }
 /* }}} */
 
-static void mmc_compress(mmc_pool_t *pool, mmc_buffer_t *buffer, const char *value, int value_len, unsigned int *flags, int copy TSRMLS_DC) /* {{{ */
+static void mmc_compress(mmc_pool_t *pool, mmc_buffer_t *buffer, const char *value, int value_len, unsigned int *flags, int copy) /* {{{ */
 {
 	/* autocompress large values */
 	if (pool->compress_threshold && value_len >= pool->compress_threshold) {
@@ -296,11 +297,11 @@ static void mmc_compress(mmc_pool_t *poo
 			prev = *buffer;
 
 			/* allocate space for prev header + result */
-			memset(buffer, 0, sizeof(*buffer));
+			ZEND_SECURE_ZERO(buffer, sizeof(*buffer));
 			mmc_buffer_alloc(buffer, prev.value.len + result_len);
 
 			/* append prev header */
-			smart_str_appendl(&(buffer->value), prev.value.c, prev.value.len - value_len);
+			smart_string_appendl(&(buffer->value), prev.value.c, prev.value.len - value_len);
 			buffer->idx = prev.idx;
 		}
 		else {
@@ -318,7 +319,7 @@ static void mmc_compress(mmc_pool_t *poo
 			buffer->value.len += result_len;
 		}
 		else {
-			smart_str_appendl(&(buffer->value), value, value_len);
+			smart_string_appendl(&(buffer->value), value, value_len);
 			*flags &= ~MMC_COMPRESSED;
 		}
 
@@ -327,7 +328,7 @@ static void mmc_compress(mmc_pool_t *poo
 		}
 	}
 	else if (!copy) {
-		smart_str_appendl(&(buffer->value), value, value_len);
+		smart_string_appendl(&(buffer->value), value, value_len);
 	}
 }
 /* }}}*/
@@ -351,11 +352,11 @@ static int mmc_uncompress(const char *da
 }
 /* }}}*/
 
-int mmc_pack_value(mmc_pool_t *pool, mmc_buffer_t *buffer, zval *value, unsigned int *flags TSRMLS_DC) /*
+int mmc_pack_value(mmc_pool_t *pool, mmc_buffer_t *buffer, zval *value, unsigned int *flags) /*
 	does serialization and compression to pack a zval into the buffer {{{ */
 {
 	if (*flags & 0xffff & ~MMC_COMPRESSED) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "The lowest two bytes of the flags array is reserved for pecl/memcache internal use");
+		php_error_docref(NULL, E_WARNING, "The lowest two bytes of the flags array is reserved for pecl/memcache internal use");
 		return MMC_REQUEST_FAILURE;
 	}
 
@@ -363,13 +364,13 @@ int mmc_pack_value(mmc_pool_t *pool, mmc
 	switch (Z_TYPE_P(value)) {
 		case IS_STRING:
 			*flags |= MMC_TYPE_STRING;
-			mmc_compress(pool, buffer, Z_STRVAL_P(value), Z_STRLEN_P(value), flags, 0 TSRMLS_CC);
+			mmc_compress(pool, buffer, Z_STRVAL_P(value), Z_STRLEN_P(value), flags, 0);
 			break;
 
 		case IS_LONG:
 			*flags |= MMC_TYPE_LONG;
 			*flags &= ~MMC_COMPRESSED;
-			smart_str_append_long(&(buffer->value), Z_LVAL_P(value));
+			smart_string_append_long(&(buffer->value), Z_LVAL_P(value));
 			break;
 
 		case IS_DOUBLE: {
@@ -377,20 +378,22 @@ int mmc_pack_value(mmc_pool_t *pool, mmc
 			int len = snprintf(buf, 256, "%.14g", Z_DVAL_P(value));
 			*flags |= MMC_TYPE_DOUBLE;
 			*flags &= ~MMC_COMPRESSED;
-			smart_str_appendl(&(buffer->value), buf, len);
+			smart_string_appendl(&(buffer->value), buf, len);
 			break;
 		}
 
-		case IS_BOOL:
+		case IS_TRUE:
+		case IS_FALSE:
 			*flags |= MMC_TYPE_BOOL;
 			*flags &= ~MMC_COMPRESSED;
-			smart_str_appendc(&(buffer->value), Z_BVAL_P(value) ? '1' : '0');
+			smart_string_appendc(&(buffer->value), Z_TYPE_P(value) == IS_TRUE ? '1' : '0');
 			break;
 
 		default: {
 			php_serialize_data_t value_hash;
 			zval value_copy, *value_copy_ptr;
 			size_t prev_len = buffer->value.len;
+			smart_str buf = {0};
 
 			/* FIXME: we should be using 'Z' instead of this, but unfortunately it's PHP5-only */
 			value_copy = *value;
@@ -398,20 +401,23 @@ int mmc_pack_value(mmc_pool_t *pool, mmc
 			value_copy_ptr = &value_copy;
 
 			PHP_VAR_SERIALIZE_INIT(value_hash);
-			php_var_serialize(&(buffer->value), &value_copy_ptr, &value_hash TSRMLS_CC);
+			php_var_serialize(&buf, value_copy_ptr, &value_hash);
 			PHP_VAR_SERIALIZE_DESTROY(value_hash);
 
+			smart_string_appendl(&(buffer->value), ZSTR_VAL(buf.s), ZSTR_LEN(buf.s));
+			smart_str_free(&buf);
+
 			/* trying to save null or something went really wrong */
 			if (buffer->value.c == NULL || buffer->value.len == prev_len) {
 				zval_dtor(&value_copy);
-				php_error_docref(NULL TSRMLS_CC, E_WARNING, "Failed to serialize value");
+				php_error_docref(NULL, E_WARNING, "Failed to serialize value");
 				return MMC_REQUEST_FAILURE;
 			}
 
 			*flags |= MMC_SERIALIZED;
 			zval_dtor(&value_copy);
 
-			mmc_compress(pool, buffer, buffer->value.c + prev_len, buffer->value.len - prev_len, flags, 1 TSRMLS_CC);
+			mmc_compress(pool, buffer, buffer->value.c + prev_len, buffer->value.len - prev_len, flags, 1);
 		}
 	}
 
@@ -421,19 +427,18 @@ int mmc_pack_value(mmc_pool_t *pool, mmc
 
 int mmc_unpack_value(
 	mmc_t *mmc, mmc_request_t *request, mmc_buffer_t *buffer, const char *key, unsigned int key_len,
-	unsigned int flags, unsigned long cas, unsigned int bytes TSRMLS_DC) /*
+	unsigned int flags, unsigned long cas, unsigned int bytes) /*
 	does uncompression and unserializing to reconstruct a zval {{{ */
 {
 	char *data = NULL;
 	unsigned long data_len;
 	int rv;
 
-	zval *object;
-	MAKE_STD_ZVAL(object);
+	zval object;
 
 	if (flags & MMC_COMPRESSED) {
 		if (mmc_uncompress(buffer->value.c, bytes, &data, &data_len) != MMC_OK) {
-			php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Failed to uncompress data");
+			php_error_docref(NULL, E_NOTICE, "Failed to uncompress data");
 			return MMC_REQUEST_DONE;
 		}
 	}
@@ -461,7 +466,7 @@ int mmc_unpack_value(
 		}
 
 		PHP_VAR_UNSERIALIZE_INIT(var_hash);
-		if (!php_var_unserialize(&object, &p, p + data_len, &var_hash TSRMLS_CC)) {
+		if (!php_var_unserialize(&object, &p, p + data_len, &var_hash)) {
 			PHP_VAR_UNSERIALIZE_DESTROY(var_hash);
 
 			if (flags & MMC_COMPRESSED) {
@@ -474,7 +479,7 @@ int mmc_unpack_value(
 				mmc_buffer_free(&buffer_tmp);
 			}
 
-			php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Failed to unserialize data");
+			php_error_docref(NULL, E_NOTICE, "Failed to unserialize data");
 			return MMC_REQUEST_DONE;
 		}
 
@@ -491,7 +496,7 @@ int mmc_unpack_value(
 		}
 
 		/* delegate to value handler */
-		return value_handler(key_tmp, key_len, object, flags, cas, value_handler_param TSRMLS_CC);
+		return value_handler(key_tmp, key_len, &object, flags, cas, value_handler_param);
 	}
 	else {
 		switch (flags & 0x0f00) {
@@ -499,7 +504,7 @@ int mmc_unpack_value(
 				long val;
 				data[data_len] = '\0';
 				val = strtol(data, NULL, 10);
-				ZVAL_LONG(object, val);
+				ZVAL_LONG(&object, val);
 				break;
 			}
 
@@ -507,17 +512,18 @@ int mmc_unpack_value(
 				double val = 0;
 				data[data_len] = '\0';
 				sscanf(data, "%lg", &val);
-				ZVAL_DOUBLE(object, val);
+				ZVAL_DOUBLE(&object, val);
 				break;
 			}
 
 			case MMC_TYPE_BOOL:
-				ZVAL_BOOL(object, data_len == 1 && data[0] == '1');
+				ZVAL_BOOL(&object, data_len == 1 && data[0] == '1');
 				break;
 
 			default:
 				data[data_len] = '\0';
-				ZVAL_STRINGL(object, data, data_len, 0);
+				ZVAL_STRINGL(&object, data, data_len);
+				efree(data);
 
 				if (!(flags & MMC_COMPRESSED)) {
 					/* release buffer because it's now owned by the zval */
@@ -526,7 +532,7 @@ int mmc_unpack_value(
 		}
 
 		/* delegate to value handler */
-		return request->value_handler(key, key_len, object, flags, cas, request->value_handler_param TSRMLS_CC);
+		return request->value_handler(key, key_len, &object, flags, cas, request->value_handler_param);
 	}
 }
 /* }}}*/
@@ -534,10 +540,10 @@ int mmc_unpack_value(
 
 mmc_t *mmc_server_new(
 	const char *host, int host_len, unsigned short tcp_port, unsigned short udp_port,
-	int persistent, double timeout, int retry_interval TSRMLS_DC) /* {{{ */
+	int persistent, double timeout, int retry_interval) /* {{{ */
 {
 	mmc_t *mmc = pemalloc(sizeof(mmc_t), persistent);
-	memset(mmc, 0, sizeof(*mmc));
+	ZEND_SECURE_ZERO(mmc, sizeof(*mmc));
 
 	mmc->host = pemalloc(host_len + 1, persistent);
 	memcpy(mmc->host, host, host_len);
@@ -560,7 +566,7 @@ mmc_t *mmc_server_new(
 }
 /* }}} */
 
-static void _mmc_server_disconnect(mmc_t *mmc, mmc_stream_t *io, int close_persistent_stream TSRMLS_DC) /* {{{ */
+static void _mmc_server_disconnect(mmc_t *mmc, mmc_stream_t *io, int close_persistent_stream) /* {{{ */
 {
 	mmc_buffer_free(&(io->buffer));
 
@@ -582,9 +588,9 @@ static void _mmc_server_disconnect(mmc_t
 }
 /* }}} */
 
-void mmc_server_disconnect(mmc_t *mmc, mmc_stream_t *io TSRMLS_DC) /* {{{ */
+void mmc_server_disconnect(mmc_t *mmc, mmc_stream_t *io) /* {{{ */
 {
-	_mmc_server_disconnect(mmc, io, 1 TSRMLS_CC);
+	_mmc_server_disconnect(mmc, io, 1);
 }
 /* }}} */
 
@@ -601,14 +607,14 @@ static void mmc_server_seterror(mmc_t *m
 }
 /* }}} */
 
-static void mmc_server_deactivate(mmc_pool_t *pool, mmc_t *mmc TSRMLS_DC) /*
+static void mmc_server_deactivate(mmc_pool_t *pool, mmc_t *mmc) /*
 	disconnect and marks the server as down, failovers all queued requests {{{ */
 {
 	mmc_queue_t readqueue;
 	mmc_request_t *request;
 
-	mmc_server_disconnect(mmc, &(mmc->tcp) TSRMLS_CC);
-	mmc_server_disconnect(mmc, &(mmc->udp) TSRMLS_CC);
+	mmc_server_disconnect(mmc, &(mmc->tcp));
+	mmc_server_disconnect(mmc, &(mmc->udp));
 
 	mmc->tcp.status = MMC_STATUS_FAILED;
 	mmc->udp.status = MMC_STATUS_FAILED;
@@ -638,19 +644,19 @@ static void mmc_server_deactivate(mmc_po
 
 	/* delegate to failover handlers */
 	while ((request = mmc_queue_pop(&readqueue)) != NULL) {
-		request->failover_handler(pool, mmc, request, request->failover_handler_param TSRMLS_CC);
+		request->failover_handler(pool, mmc, request, request->failover_handler_param);
 	}
 
 	mmc_queue_free(&readqueue);
 
 	/* fire userspace failure event */
 	if (pool->failure_callback != NULL) {
-		pool->failure_callback(pool, mmc, pool->failure_callback_param TSRMLS_CC);
+		pool->failure_callback(pool, mmc, &pool->failure_callback_param);
 	}
 }
 /* }}} */
 
-int mmc_server_failure(mmc_t *mmc, mmc_stream_t *io, const char *error, int errnum TSRMLS_DC) /*
+int mmc_server_failure(mmc_t *mmc, mmc_stream_t *io, const char *error, int errnum) /*
 	determines if a request should be retried or is a hard network failure {{{ */
 {
 	switch (io->status) {
@@ -668,36 +674,35 @@ int mmc_server_failure(mmc_t *mmc, mmc_s
 }
 /* }}} */
 
-int mmc_request_failure(mmc_t *mmc, mmc_stream_t *io, const char *message, unsigned int message_len, int errnum TSRMLS_DC) /*
+int mmc_request_failure(mmc_t *mmc, mmc_stream_t *io, const char *message, unsigned int message_len, int errnum) /*
 	 checks for a valid server generated error message and calls mmc_server_failure() {{{ */
 {
 	if (message_len) {
-		return mmc_server_failure(mmc, io, message, errnum TSRMLS_CC);
+		return mmc_server_failure(mmc, io, message, errnum);
 	}
 
-	return mmc_server_failure(mmc, io, "Malformed server response", errnum TSRMLS_CC);
+	return mmc_server_failure(mmc, io, "Malformed server response", errnum);
 }
 /* }}} */
 
-static int mmc_server_connect(mmc_pool_t *pool, mmc_t *mmc, mmc_stream_t *io, int udp TSRMLS_DC) /*
+static int mmc_server_connect(mmc_pool_t *pool, mmc_t *mmc, mmc_stream_t *io, int udp) /*
 	connects a stream, calls mmc_server_deactivate() on failure {{{ */
 {
-	char *host, *hash_key = NULL, *errstr = NULL;
+	char *host, *hash_key = NULL;
+	zend_string *errstr = NULL;
 	int	host_len, errnum = 0;
 	struct timeval tv = mmc->timeout;
 	int fd;
 
 	/* close open stream */
 	if (io->stream != NULL) {
-		mmc_server_disconnect(mmc, io TSRMLS_CC);
+		mmc_server_disconnect(mmc, io);
 	}
 
 	if (mmc->persistent) {
 		spprintf(&hash_key, 0, "memcache:stream:%s:%u:%d", mmc->host, io->port, udp);
 	}
 
-#if PHP_API_VERSION > 20020918
-
 	if (udp) {
 		host_len = spprintf(&host, 0, "udp://%s:%u", mmc->host, io->port);
 	}
@@ -710,51 +715,20 @@ static int mmc_server_connect(mmc_pool_t
 
 	io->stream = php_stream_xport_create(
 		host, host_len,
-		ENFORCE_SAFE_MODE | REPORT_ERRORS | (mmc->persistent ? STREAM_OPEN_PERSISTENT : 0),
+		REPORT_ERRORS | (mmc->persistent ? STREAM_OPEN_PERSISTENT : 0),
 		STREAM_XPORT_CLIENT | STREAM_XPORT_CONNECT,
 		hash_key, &tv, NULL, &errstr, &errnum);
 
 	efree(host);
 
-#else
-
-	if (mmc->persistent) {
-		switch (php_stream_from_persistent_id(hash_key, &(io->stream) TSRMLS_CC)) {
-			case PHP_STREAM_PERSISTENT_SUCCESS:
-				if (php_stream_eof(io->stream)) {
-					php_stream_pclose(io->stream);
-					io->stream = NULL;
-					io->fd = 0;
-					break;
-				}
-			case PHP_STREAM_PERSISTENT_FAILURE:
-				break;
-		}
-	}
-
-	if (io->stream == NULL) {
-		if (io->port) {
-			io->stream = php_stream_sock_open_host(mmc->host, io->port, udp ? SOCK_DGRAM : SOCK_STREAM, &tv, hash_key);
-		}
-		else if (strncasecmp("unix://", mmc->host, sizeof("unix://")-1) == 0 && strlen(mmc->host) > sizeof("unix://")-1) {
-			io->stream = php_stream_sock_open_unix(mmc->host + sizeof("unix://")-1, strlen(mmc->host + sizeof("unix://")-1), hash_key, &tv);
-		}
-		else {
-			io->stream = php_stream_sock_open_unix(mmc->host, strlen(mmc->host), hash_key, &tv);
-		}
-	}
-
-#endif
-
 	if (hash_key != NULL) {
 		efree(hash_key);
 	}
 
 	/* check connection and extract socket for select() purposes */
-
 	if (!io->stream || php_stream_cast(io->stream, PHP_STREAM_AS_FD_FOR_SELECT, (void **)&fd, 1) != SUCCESS) {
-		mmc_server_seterror(mmc, errstr != NULL ? errstr : "Connection failed", errnum);
-		mmc_server_deactivate(pool, mmc TSRMLS_CC);
+		mmc_server_seterror(mmc, errstr != NULL ? ZSTR_VAL(errstr) : "Connection failed", errnum);
+		mmc_server_deactivate(pool, mmc);
 
 		if (errstr != NULL) {
 			efree(errstr);
@@ -762,10 +736,6 @@ static int mmc_server_connect(mmc_pool_t
 
 		return MMC_REQUEST_FAILURE;
 	}
-
-	io->fd = fd;
-	io->status = MMC_STATUS_CONNECTED;
-
 	php_stream_auto_cleanup(io->stream);
 	php_stream_set_chunk_size(io->stream, io->chunk_size);
 	php_stream_set_option(io->stream, PHP_STREAM_OPTION_BLOCKING, 0, NULL);
@@ -775,6 +745,9 @@ static int mmc_server_connect(mmc_pool_t
 	php_stream_set_option(io->stream, PHP_STREAM_OPTION_READ_BUFFER, PHP_STREAM_BUFFER_NONE, NULL);
 	php_stream_set_option(io->stream, PHP_STREAM_OPTION_WRITE_BUFFER, PHP_STREAM_BUFFER_NONE, NULL);
 
+	io->fd = fd;
+	io->status = MMC_STATUS_CONNECTED;
+
 	/* php_stream buffering prevent us from detecting datagram boundaries when using udp */
 	if (udp) {
 		io->read = mmc_stream_read_buffered;
@@ -802,7 +775,7 @@ static int mmc_server_connect(mmc_pool_t
 }
 /* }}} */
 
-int mmc_server_valid(mmc_t *mmc TSRMLS_DC) /*
+int mmc_server_valid(mmc_t *mmc) /*
 	checks if a server should be considered valid to serve requests {{{ */
 {
 	if (mmc != NULL) {
@@ -820,7 +793,7 @@ int mmc_server_valid(mmc_t *mmc TSRMLS_D
 }
 /* }}} */
 
-void mmc_server_sleep(mmc_t *mmc TSRMLS_DC) /*
+void mmc_server_sleep(mmc_t *mmc) /*
 	prepare server struct for persistent sleep {{{ */
 {
 	mmc_buffer_free(&(mmc->tcp.buffer));
@@ -840,18 +813,18 @@ void mmc_server_sleep(mmc_t *mmc TSRMLS_
 }
 /* }}} */
 
-void mmc_server_free(mmc_t *mmc TSRMLS_DC) /* {{{ */
+void mmc_server_free(mmc_t *mmc) /* {{{ */
 {
-	mmc_server_sleep(mmc TSRMLS_CC);
-	_mmc_server_disconnect(mmc, &(mmc->tcp), 0 TSRMLS_CC);
-	_mmc_server_disconnect(mmc, &(mmc->udp), 0 TSRMLS_CC);
+	mmc_server_sleep(mmc);
+	_mmc_server_disconnect(mmc, &(mmc->tcp), 0);
+	_mmc_server_disconnect(mmc, &(mmc->udp), 0);
 
 	pefree(mmc->host, mmc->persistent);
 	pefree(mmc, mmc->persistent);
 }
 /* }}} */
 
-static void mmc_pool_init_hash(mmc_pool_t *pool TSRMLS_DC) /* {{{ */
+static void mmc_pool_init_hash(mmc_pool_t *pool) /* {{{ */
 {
 	mmc_hash_function_t *hash;
 
@@ -875,10 +848,10 @@ static void mmc_pool_init_hash(mmc_pool_
 }
 /* }}} */
 
-mmc_pool_t *mmc_pool_new(TSRMLS_D) /* {{{ */
+mmc_pool_t *mmc_pool_new() /* {{{ */
 {
 	mmc_pool_t *pool = emalloc(sizeof(mmc_pool_t));
-	memset(pool, 0, sizeof(*pool));
+	ZEND_SECURE_ZERO(pool, sizeof(*pool));
 
 	switch (MEMCACHE_G(protocol)) {
 		case MMC_BINARY_PROTOCOL:
@@ -888,7 +861,7 @@ mmc_pool_t *mmc_pool_new(TSRMLS_D) /* {{
 			pool->protocol = &mmc_ascii_protocol;
 	}
 
-	mmc_pool_init_hash(pool TSRMLS_CC);
+	mmc_pool_init_hash(pool);
 	pool->compress_threshold = MEMCACHE_G(compress_threshold);
 	pool->min_compress_savings = MMC_DEFAULT_SAVINGS;
 
@@ -899,7 +872,7 @@ mmc_pool_t *mmc_pool_new(TSRMLS_D) /* {{
 }
 /* }}} */
 
-void mmc_pool_free(mmc_pool_t *pool TSRMLS_DC) /* {{{ */
+void mmc_pool_free(mmc_pool_t *pool) /* {{{ */
 {
 	int i;
 	mmc_request_t *request;
@@ -907,9 +880,9 @@ void mmc_pool_free(mmc_pool_t *pool TSRM
 	for (i=0; i<pool->num_servers; i++) {
 		if (pool->servers[i] != NULL) {
 			if (pool->servers[i]->persistent) {
-				mmc_server_sleep(pool->servers[i] TSRMLS_CC);
+				mmc_server_sleep(pool->servers[i]);
 			} else {
-				mmc_server_free(pool->servers[i] TSRMLS_CC);
+				mmc_server_free(pool->servers[i]);
 			}
 			pool->servers[i] = NULL;
 		}
@@ -953,7 +926,7 @@ void mmc_pool_add(mmc_pool_t *pool, mmc_
 }
 /* }}} */
 
-void mmc_pool_close(mmc_pool_t *pool TSRMLS_DC) /*
+void mmc_pool_close(mmc_pool_t *pool) /*
 	disconnects and removes all servers in the pool {{{ */
 {
 	if (pool->num_servers) {
@@ -961,9 +934,9 @@ void mmc_pool_close(mmc_pool_t *pool TSR
 
 		for (i=0; i<pool->num_servers; i++) {
 			if (pool->servers[i]->persistent) {
-				mmc_server_sleep(pool->servers[i] TSRMLS_CC);
+				mmc_server_sleep(pool->servers[i]);
 			} else {
-				mmc_server_free(pool->servers[i] TSRMLS_CC);
+				mmc_server_free(pool->servers[i]);
 			}
 		}
 
@@ -973,12 +946,12 @@ void mmc_pool_close(mmc_pool_t *pool TSR
 
 		/* reallocate the hash strategy state */
 		pool->hash->free_state(pool->hash_state);
-		mmc_pool_init_hash(pool TSRMLS_CC);
+		mmc_pool_init_hash(pool);
 	}
 }
 /* }}} */
 
-int mmc_pool_open(mmc_pool_t *pool, mmc_t *mmc, mmc_stream_t *io, int udp TSRMLS_DC) /*
+int mmc_pool_open(mmc_pool_t *pool, mmc_t *mmc, mmc_stream_t *io, int udp) /*
 	connects if the stream is not already connected {{{ */
 {
 	switch (io->status) {
@@ -988,14 +961,15 @@ int mmc_pool_open(mmc_pool_t *pool, mmc_
 
 		case MMC_STATUS_DISCONNECTED:
 		case MMC_STATUS_FAILED:
-			return mmc_server_connect(pool, mmc, io, udp TSRMLS_CC);
+
+			return mmc_server_connect(pool, mmc, io, udp);
 	}
 
 	return MMC_REQUEST_FAILURE;
 }
 /* }}} */
 
-mmc_t *mmc_pool_find_next(mmc_pool_t *pool, const char *key, unsigned int key_len, mmc_queue_t *skip_servers, unsigned int *last_index TSRMLS_DC) /*
+mmc_t *mmc_pool_find_next(mmc_pool_t *pool, const char *key, unsigned int key_len, mmc_queue_t *skip_servers, unsigned int *last_index) /*
 	finds the next server in the failover sequence {{{ */
 {
 	mmc_t *mmc;
@@ -1005,40 +979,40 @@ mmc_t *mmc_pool_find_next(mmc_pool_t *po
 	/* find the next server not present in the skip-list */
 	do {
 		keytmp_len = sprintf(keytmp, "%s-%d", key, (*last_index)++);
-		mmc = pool->hash->find_server(pool->hash_state, keytmp, keytmp_len TSRMLS_CC);
+		mmc = pool->hash->find_server(pool->hash_state, keytmp, keytmp_len);
 	} while (mmc_queue_contains(skip_servers, mmc) && *last_index < MEMCACHE_G(max_failover_attempts));
 
 	return mmc;
 }
 
-mmc_t *mmc_pool_find(mmc_pool_t *pool, const char *key, unsigned int key_len TSRMLS_DC) /*
+mmc_t *mmc_pool_find(mmc_pool_t *pool, const char *key, unsigned int key_len) /*
 	maps a key to a non-failed server {{{ */
 {
-	mmc_t *mmc = pool->hash->find_server(pool->hash_state, key, key_len TSRMLS_CC);
+	mmc_t *mmc = pool->hash->find_server(pool->hash_state, key, key_len);
 
 	/* check validity and try to failover otherwise */
-	if (!mmc_server_valid(mmc TSRMLS_CC) && MEMCACHE_G(allow_failover)) {
+	if (!mmc_server_valid(mmc) && MEMCACHE_G(allow_failover)) {
 		unsigned int last_index = 0;
 
 		do {
-			mmc = mmc_pool_find_next(pool, key, key_len, NULL, &last_index TSRMLS_CC);
-		} while (!mmc_server_valid(mmc TSRMLS_CC) && last_index < MEMCACHE_G(max_failover_attempts));
+			mmc = mmc_pool_find_next(pool, key, key_len, NULL, &last_index);
+		} while (!mmc_server_valid(mmc) && last_index < MEMCACHE_G(max_failover_attempts));
 	}
 
 	return mmc;
 }
 /* }}} */
 
-int mmc_pool_failover_handler(mmc_pool_t *pool, mmc_t *mmc, mmc_request_t *request, void *param TSRMLS_DC) /*
+int mmc_pool_failover_handler(mmc_pool_t *pool, mmc_t *mmc, mmc_request_t *request, void *param) /*
 	uses request->key to reschedule request to other server {{{ */
 {
 	if (MEMCACHE_G(allow_failover) && request->failed_index < MEMCACHE_G(max_failover_attempts) && request->failed_servers.len < pool->num_servers) {
 		do {
 			mmc_queue_push(&(request->failed_servers), mmc);
-			mmc = mmc_pool_find_next(pool, request->key, request->key_len, &(request->failed_servers), &(request->failed_index) TSRMLS_CC);
-		} while (!mmc_server_valid(mmc TSRMLS_CC) && request->failed_index < MEMCACHE_G(max_failover_attempts) && request->failed_servers.len < pool->num_servers);
+			mmc = mmc_pool_find_next(pool, request->key, request->key_len, &(request->failed_servers), &(request->failed_index));
+		} while (!mmc_server_valid(mmc) && request->failed_index < MEMCACHE_G(max_failover_attempts) && request->failed_servers.len < pool->num_servers);
 
-		return mmc_pool_schedule(pool, mmc, request TSRMLS_CC);
+		return mmc_pool_schedule(pool, mmc, request);
 	}
 
 	mmc_pool_release(pool, request);
@@ -1046,7 +1020,7 @@ int mmc_pool_failover_handler(mmc_pool_t
 }
 /* }}}*/
 
-int mmc_pool_failover_handler_null(mmc_pool_t *pool, mmc_t *mmc, mmc_request_t *request, void *param TSRMLS_DC) /*
+int mmc_pool_failover_handler_null(mmc_pool_t *pool, mmc_t *mmc, mmc_request_t *request, void *param) /*
 	always returns failure {{{ */
 {
 	mmc_pool_release(pool, request);
@@ -1054,7 +1028,7 @@ int mmc_pool_failover_handler_null(mmc_p
 }
 /* }}}*/
 
-static int mmc_pool_response_handler_null(mmc_t *mmc, mmc_request_t *request, int response, const char *message, unsigned int message_len, void *param TSRMLS_DC) /*
+static int mmc_pool_response_handler_null(mmc_t *mmc, mmc_request_t *request, int response, const char *message, unsigned int message_len, void *param) /*
 	always returns done {{{ */
 {
 	return MMC_REQUEST_DONE;
@@ -1062,7 +1036,7 @@ static int mmc_pool_response_handler_nul
 /* }}}*/
 
 static inline mmc_request_t *mmc_pool_request_alloc(mmc_pool_t *pool, int protocol,
-	mmc_request_failover_handler failover_handler, void *failover_handler_param TSRMLS_DC) /* {{{ */
+	mmc_request_failover_handler failover_handler, void *failover_handler_param) /* {{{ */
 {
 	mmc_request_t *request = mmc_queue_pop(&(pool->free_requests));
 	if (request == NULL) {
@@ -1076,7 +1050,7 @@ static inline mmc_request_t *mmc_pool_re
 
 	if (protocol == MMC_PROTO_UDP) {
 		mmc_udp_header_t header = {0};
-		smart_str_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));
+		smart_string_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));
 	}
 
 	request->failover_handler = failover_handler != NULL ? failover_handler : mmc_pool_failover_handler_null;
@@ -1088,10 +1062,10 @@ static inline mmc_request_t *mmc_pool_re
 
 mmc_request_t *mmc_pool_request(mmc_pool_t *pool, int protocol,
 	mmc_request_response_handler response_handler, void *response_handler_param,
-	mmc_request_failover_handler failover_handler, void *failover_handler_param TSRMLS_DC) /*
+	mmc_request_failover_handler failover_handler, void *failover_handler_param) /*
 	allocates a request, must be added to pool using mmc_pool_schedule or released with mmc_pool_release {{{ */
 {
-	mmc_request_t *request = mmc_pool_request_alloc(pool, protocol, failover_handler, failover_handler_param TSRMLS_CC);
+	mmc_request_t *request = mmc_pool_request_alloc(pool, protocol, failover_handler, failover_handler_param);
 	request->response_handler = response_handler;
 	request->response_handler_param = response_handler_param;
 	return request;
@@ -1100,13 +1074,13 @@ mmc_request_t *mmc_pool_request(mmc_pool
 
 mmc_request_t *mmc_pool_request_get(mmc_pool_t *pool, int protocol,
 	mmc_request_value_handler value_handler, void *value_handler_param,
-	mmc_request_failover_handler failover_handler, void *failover_handler_param TSRMLS_DC) /*
+	mmc_request_failover_handler failover_handler, void *failover_handler_param) /*
 	allocates a request, must be added to pool using mmc_pool_schedule or released with mmc_pool_release {{{ */
 {
 	mmc_request_t *request = mmc_pool_request(
 		pool, protocol,
 		mmc_pool_response_handler_null, NULL,
-		failover_handler, failover_handler_param TSRMLS_CC);
+		failover_handler, failover_handler_param);
 
 	request->value_handler = value_handler;
 	request->value_handler_param = value_handler_param;
@@ -1114,10 +1088,10 @@ mmc_request_t *mmc_pool_request_get(mmc_
 }
 /* }}} */
 
-mmc_request_t *mmc_pool_clone_request(mmc_pool_t *pool, mmc_request_t *request TSRMLS_DC) /*
+mmc_request_t *mmc_pool_clone_request(mmc_pool_t *pool, mmc_request_t *request) /*
 	clones a request, must be added to pool using mmc_pool_schedule or released with mmc_pool_release {{{ */
 {
-	mmc_request_t *clone = mmc_pool_request_alloc(pool, request->protocol, NULL, NULL TSRMLS_CC);
+	mmc_request_t *clone = mmc_pool_request_alloc(pool, request->protocol, NULL, NULL);
 
 	clone->response_handler = request->response_handler;
 	clone->response_handler_param = request->response_handler_param;
@@ -1143,13 +1117,13 @@ mmc_request_t *mmc_pool_clone_request(mm
 }
 /* }}} */
 
-static int mmc_pool_slot_send(mmc_pool_t *pool, mmc_t *mmc, mmc_request_t *request, int handle_failover TSRMLS_DC) /* {{{ */
+static int mmc_pool_slot_send(mmc_pool_t *pool, mmc_t *mmc, mmc_request_t *request, int handle_failover) /* {{{ */
 {
 	if (request != NULL) {
 		/* select protocol strategy and open connection */
 		if (request->protocol == MMC_PROTO_UDP && mmc->udp.port &&
 			request->sendbuf.value.len <= mmc->udp.chunk_size &&
-			mmc_pool_open(pool, mmc, &(mmc->udp), 1 TSRMLS_CC) == MMC_OK)
+			mmc_pool_open(pool, mmc, &(mmc->udp), 1) == MMC_OK)
 		{
 			request->io = &(mmc->udp);
 			request->read = mmc_request_read_udp;
@@ -1162,7 +1136,7 @@ static int mmc_pool_slot_send(mmc_pool_t
 			((mmc_udp_header_t *)request->sendbuf.value.c)->reqid = htons(request->udp.reqid);
 			((mmc_udp_header_t *)request->sendbuf.value.c)->total = htons(1);
 		}
-		else if (mmc_pool_open(pool, mmc, &(mmc->tcp), 0 TSRMLS_CC) == MMC_OK) {
+		else if (mmc_pool_open(pool, mmc, &(mmc->tcp), 0) == MMC_OK) {
 			/* skip udp header */
 			if (request->protocol == MMC_PROTO_UDP) {
 				request->sendbuf.idx += sizeof(mmc_udp_header_t);
@@ -1174,7 +1148,7 @@ static int mmc_pool_slot_send(mmc_pool_t
 		else {
 			mmc->sendreq = NULL;
 			if (handle_failover) {
-				return request->failover_handler(pool, mmc, request, request->failover_handler_param TSRMLS_CC);
+				return request->failover_handler(pool, mmc, request, request->failover_handler_param);
 			}
 			return MMC_REQUEST_FAILURE;
 		}
@@ -1185,12 +1159,12 @@ static int mmc_pool_slot_send(mmc_pool_t
 }
 /* }}} */
 
-int mmc_pool_schedule(mmc_pool_t *pool, mmc_t *mmc, mmc_request_t *request TSRMLS_DC) /*
+int mmc_pool_schedule(mmc_pool_t *pool, mmc_t *mmc, mmc_request_t *request) /*
 	schedules a request against a server, return MMC_OK on success {{{ */
 {
-	if (!mmc_server_valid(mmc TSRMLS_CC)) {
+	if (!mmc_server_valid(mmc)) {
 		/* delegate to failover handler if connect fails */
-		return request->failover_handler(pool, mmc, request, request->failover_handler_param TSRMLS_CC);
+		return request->failover_handler(pool, mmc, request, request->failover_handler_param);
 	}
 
 	/* reset sendbuf to start position */
@@ -1200,8 +1174,8 @@ int mmc_pool_schedule(mmc_pool_t *pool,
 
 	/* push request into sendreq slot if available */
 	if (mmc->sendreq == NULL) {
-		if (mmc_pool_slot_send(pool, mmc, request, 0 TSRMLS_CC) != MMC_OK) {
-			return request->failover_handler(pool, mmc, request, request->failover_handler_param TSRMLS_CC);
+		if (mmc_pool_slot_send(pool, mmc, request, 0) != MMC_OK) {
+			return request->failover_handler(pool, mmc, request, request->failover_handler_param);
 		}
 		mmc_queue_push(pool->sending, mmc);
 	}
@@ -1222,7 +1196,7 @@ int mmc_pool_schedule(mmc_pool_t *pool,
 }
 /* }}} */
 
-int mmc_pool_schedule_key(mmc_pool_t *pool, const char *key, unsigned int key_len, mmc_request_t *request, unsigned int redundancy TSRMLS_DC) /*
+int mmc_pool_schedule_key(mmc_pool_t *pool, const char *key, unsigned int key_len, mmc_request_t *request, unsigned int redundancy) /*
 	schedules a request against a server selected by the provided key, return MMC_OK on success {{{ */
 {
 	if (redundancy > 1) {
@@ -1233,16 +1207,16 @@ int mmc_pool_schedule_key(mmc_pool_t *po
 		mmc_queue_t skip_servers = {0};
 
 		/* schedule the first request */
-		mmc = mmc_pool_find(pool, key, key_len TSRMLS_CC);
-		result = mmc_pool_schedule(pool, mmc, request TSRMLS_CC);
+		mmc = mmc_pool_find(pool, key, key_len);
+		result = mmc_pool_schedule(pool, mmc, request);
 
 		/* clone and schedule redundancy-1 additional requests */
 		for (i=0; i < redundancy-1 && i < pool->num_servers-1; i++) {
 			mmc_queue_push(&skip_servers, mmc);
-			mmc = mmc_pool_find_next(pool, key, key_len, &skip_servers, &last_index TSRMLS_CC);
+			mmc = mmc_pool_find_next(pool, key, key_len, &skip_servers, &last_index);
 
-			if (mmc_server_valid(mmc TSRMLS_CC)) {
-				mmc_pool_schedule(pool, mmc, mmc_pool_clone_request(pool, request TSRMLS_CC) TSRMLS_CC);
+			if (mmc_server_valid(mmc)) {
+				mmc_pool_schedule(pool, mmc, mmc_pool_clone_request(pool, request));
 			}
 		}
 
@@ -1250,7 +1224,7 @@ int mmc_pool_schedule_key(mmc_pool_t *po
 		return result;
 	}
 
-	return mmc_pool_schedule(pool, mmc_pool_find(pool, key, key_len TSRMLS_CC), request TSRMLS_CC);
+	return mmc_pool_schedule(pool, mmc_pool_find(pool, key, key_len), request);
 }
 /* }}} */
 
@@ -1258,7 +1232,7 @@ int mmc_pool_schedule_get(
 	mmc_pool_t *pool, int protocol, int op, zval *zkey,
 	mmc_request_value_handler value_handler, void *value_handler_param,
 	mmc_request_failover_handler failover_handler, void *failover_handler_param,
-	mmc_request_t *failed_request TSRMLS_DC) /*
+	mmc_request_t *failed_request) /*
 	schedules a get command against a server {{{ */
 {
 	mmc_t *mmc;
@@ -1266,12 +1240,12 @@ int mmc_pool_schedule_get(
 	unsigned int key_len;
 
 	if (mmc_prepare_key(zkey, key, &key_len) != MMC_OK) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid key");
+		php_error_docref(NULL, E_WARNING, "Invalid key");
 		return MMC_REQUEST_FAILURE;
 	}
 
-	mmc = mmc_pool_find(pool, key, key_len TSRMLS_CC);
-	if (!mmc_server_valid(mmc TSRMLS_CC)) {
+	mmc = mmc_pool_find(pool, key, key_len);
+	if (!mmc_server_valid(mmc)) {
 		return MMC_REQUEST_FAILURE;
 	}
 
@@ -1280,7 +1254,7 @@ int mmc_pool_schedule_get(
 
 		mmc->buildreq = mmc_pool_request_get(
 			pool, protocol, value_handler, value_handler_param,
-			failover_handler, failover_handler_param TSRMLS_CC);
+			failover_handler, failover_handler_param);
 
 		if (failed_request != NULL) {
 			mmc_queue_copy(&(mmc->buildreq->failed_servers), &(failed_request->failed_servers));
@@ -1292,14 +1266,14 @@ int mmc_pool_schedule_get(
 	else if (protocol == MMC_PROTO_UDP && mmc->buildreq->sendbuf.value.len + key_len + 3 > MMC_MAX_UDP_LEN) {
 		/* datagram if full, schedule for delivery */
 		pool->protocol->end_get(mmc->buildreq);
-		mmc_pool_schedule(pool, mmc, mmc->buildreq TSRMLS_CC);
+		mmc_pool_schedule(pool, mmc, mmc->buildreq);
 
 		/* begin sending requests immediatly */
-		mmc_pool_select(pool TSRMLS_CC);
+		mmc_pool_select(pool);
 
 		mmc->buildreq = mmc_pool_request_get(
 			pool, protocol, value_handler, value_handler_param,
-			failover_handler, failover_handler_param TSRMLS_CC);
+			failover_handler, failover_handler_param);
 
 		if (failed_request != NULL) {
 			mmc_queue_copy(&(mmc->buildreq->failed_servers), &(failed_request->failed_servers));
@@ -1330,11 +1304,11 @@ static inline void mmc_pool_switch(mmc_p
 	mmc_queue_reset(pool->reading);
 }
 
-static int mmc_select_failure(mmc_pool_t *pool, mmc_t *mmc, mmc_request_t *request, int result TSRMLS_DC) /* {{{ */
+static int mmc_select_failure(mmc_pool_t *pool, mmc_t *mmc, mmc_request_t *request, int result) /* {{{ */
 {
 	if (result == 0) {
 		/* timeout expired, non-responsive server */
-		if (mmc_server_failure(mmc, request->io, "Network timeout", 0 TSRMLS_CC) == MMC_REQUEST_RETRY) {
+		if (mmc_server_failure(mmc, request->io, "Network timeout", 0) == MMC_REQUEST_RETRY) {
 			return MMC_REQUEST_RETRY;
 		}
 	}
@@ -1354,12 +1328,12 @@ static int mmc_select_failure(mmc_pool_t
 	}
 
 	/* hard failure, deactivate connection */
-	mmc_server_deactivate(pool, mmc TSRMLS_CC);
+	mmc_server_deactivate(pool, mmc);
 	return MMC_REQUEST_FAILURE;
 }
 /* }}} */
 
-static void mmc_select_retry(mmc_pool_t *pool, mmc_t *mmc, mmc_request_t *request TSRMLS_DC) /*
+static void mmc_select_retry(mmc_pool_t *pool, mmc_t *mmc, mmc_request_t *request) /*
 	removes request from send/read queues and calls failover {{{ */
 {
 	/* clear out failed request from queues */
@@ -1368,7 +1342,7 @@ static void mmc_select_retry(mmc_pool_t
 
 	/* shift next request into send slot */
 	if (mmc->sendreq == request) {
-		mmc_pool_slot_send(pool, mmc, mmc_queue_pop(&(mmc->sendqueue)), 1 TSRMLS_CC);
+		mmc_pool_slot_send(pool, mmc, mmc_queue_pop(&(mmc->sendqueue)), 1);
 
 		/* clear out connection from send queue if no new request was slotted */
 		if (!mmc->sendreq) {
@@ -1386,11 +1360,11 @@ static void mmc_select_retry(mmc_pool_t
 		}
 	}
 
-	request->failover_handler(pool, mmc, request, request->failover_handler_param TSRMLS_CC);
+	request->failover_handler(pool, mmc, request, request->failover_handler_param);
 }
 /* }}} */
 
-void mmc_pool_select(mmc_pool_t *pool TSRMLS_DC) /*
+void mmc_pool_select(mmc_pool_t *pool) /*
 	runs one select() round on all scheduled requests {{{ */
 {
 	int i, fd, result;
@@ -1448,9 +1422,9 @@ void mmc_pool_select(mmc_pool_t *pool TS
 					mmc_queue_remove(reading, mmc);
 					i--;
 
-					if (mmc_select_failure(pool, mmc, mmc->sendreq, result TSRMLS_CC) == MMC_REQUEST_RETRY) {
+					if (mmc_select_failure(pool, mmc, mmc->sendreq, result) == MMC_REQUEST_RETRY) {
 						/* allow request to try and send again */
-						mmc_select_retry(pool, mmc, mmc->sendreq TSRMLS_CC);
+						mmc_select_retry(pool, mmc, mmc->sendreq);
 					}
 				}
 			}
@@ -1464,9 +1438,9 @@ void mmc_pool_select(mmc_pool_t *pool TS
 					mmc_queue_remove(reading, mmc);
 					i--;
 
-					if (mmc_select_failure(pool, mmc, mmc->readreq, result TSRMLS_CC) == MMC_REQUEST_RETRY) {
+					if (mmc_select_failure(pool, mmc, mmc->readreq, result) == MMC_REQUEST_RETRY) {
 						/* allow request to try and read again */
-						mmc_select_retry(pool, mmc, mmc->readreq TSRMLS_CC);
+						mmc_select_retry(pool, mmc, mmc->readreq);
 					}
 				}
 			}
@@ -1492,7 +1466,7 @@ void mmc_pool_select(mmc_pool_t *pool TS
 			/* until stream buffer is empty */
 			do {
 				/* delegate to request send handler */
-				result = mmc_request_send(mmc, mmc->sendreq TSRMLS_CC);
+				result = mmc_request_send(mmc, mmc->sendreq);
 
 				/* check if someone has helped complete our run */
 				if (!pool->in_select) {
@@ -1502,7 +1476,7 @@ void mmc_pool_select(mmc_pool_t *pool TS
 				switch (result) {
 					case MMC_REQUEST_FAILURE:
 						/* take server offline and failover requests */
-						mmc_server_deactivate(pool, mmc TSRMLS_CC);
+						mmc_server_deactivate(pool, mmc);
 
 						/* server is failed, remove from read queue */
 						mmc_queue_remove(reading, mmc);
@@ -1510,12 +1484,12 @@ void mmc_pool_select(mmc_pool_t *pool TS
 
 					case MMC_REQUEST_RETRY:
 						/* allow request to reschedule itself */
-						mmc_select_retry(pool, mmc, mmc->sendreq TSRMLS_CC);
+						mmc_select_retry(pool, mmc, mmc->sendreq);
 						break;
 
 					case MMC_REQUEST_DONE:
 						/* shift next request into send slot */
-						mmc_pool_slot_send(pool, mmc, mmc_queue_pop(&(mmc->sendqueue)), 1 TSRMLS_CC);
+						mmc_pool_slot_send(pool, mmc, mmc_queue_pop(&(mmc->sendqueue)), 1);
 						break;
 
 					case MMC_REQUEST_MORE:
@@ -1523,7 +1497,7 @@ void mmc_pool_select(mmc_pool_t *pool TS
 						break;
 
 					default:
-						php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid return value, bailing out");
+						php_error_docref(NULL, E_ERROR, "Invalid return value, bailing out");
 				}
 			} while (mmc->sendreq != NULL && (result == MMC_REQUEST_DONE || result == MMC_REQUEST_AGAIN));
 
@@ -1554,18 +1528,18 @@ void mmc_pool_select(mmc_pool_t *pool TS
 
 			/* fill read buffer if needed */
 			if (mmc->readreq->read != NULL) {
-				result = mmc->readreq->read(mmc, mmc->readreq TSRMLS_CC);
+				result = mmc->readreq->read(mmc, mmc->readreq);
 
 				if (result != MMC_OK) {
 					switch (result) {
 						case MMC_REQUEST_FAILURE:
 							/* take server offline and failover requests */
-							mmc_server_deactivate(pool, mmc TSRMLS_CC);
+							mmc_server_deactivate(pool, mmc);
 							break;
 
 						case MMC_REQUEST_RETRY:
 							/* allow request to reschedule itself */
-							mmc_select_retry(pool, mmc, mmc->readreq TSRMLS_CC);
+							mmc_select_retry(pool, mmc, mmc->readreq);
 							break;
 
 						case MMC_REQUEST_MORE:
@@ -1574,7 +1548,7 @@ void mmc_pool_select(mmc_pool_t *pool TS
 							break;
 
 						default:
-							php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid return value, bailing out");
+							php_error_docref(NULL, E_ERROR, "Invalid return value, bailing out");
 					}
 
 					/* skip to next request */
@@ -1585,7 +1559,7 @@ void mmc_pool_select(mmc_pool_t *pool TS
 			/* until stream buffer is empty */
 			do {
 				/* delegate to request response handler */
-				result = mmc->readreq->parse(mmc, mmc->readreq TSRMLS_CC);
+				result = mmc->readreq->parse(mmc, mmc->readreq);
 
 				/* check if someone has helped complete our run */
 				if (!pool->in_select) {
@@ -1595,22 +1569,22 @@ void mmc_pool_select(mmc_pool_t *pool TS
 				switch (result) {
 					case MMC_REQUEST_FAILURE:
 						/* take server offline and failover requests */
-						mmc_server_deactivate(pool, mmc TSRMLS_CC);
+						mmc_server_deactivate(pool, mmc);
 						break;
 
 					case MMC_REQUEST_RETRY:
 						/* allow request to reschedule itself */
-						mmc_select_retry(pool, mmc, mmc->readreq TSRMLS_CC);
+						mmc_select_retry(pool, mmc, mmc->readreq);
 						break;
 
 					case MMC_REQUEST_DONE:
 						/* might have completed without having sent all data (e.g. object too large errors) */
 						if (mmc->sendreq == mmc->readreq) {
 							/* disconnect stream since data may have been sent before we received the SERVER_ERROR */
-							mmc_server_disconnect(mmc, mmc->readreq->io TSRMLS_CC);
+							mmc_server_disconnect(mmc, mmc->readreq->io);
 
 							/* shift next request into send slot */
-							mmc_pool_slot_send(pool, mmc, mmc_queue_pop(&(mmc->sendqueue)), 1 TSRMLS_CC);
+							mmc_pool_slot_send(pool, mmc, mmc_queue_pop(&(mmc->sendqueue)), 1);
 
 							/* clear out connection from send queue if no new request was slotted */
 							if (!mmc->sendreq) {
@@ -1628,10 +1602,10 @@ void mmc_pool_select(mmc_pool_t *pool TS
 					case MMC_REQUEST_MORE:
 						/* read more data from socket */
 						if (php_stream_eof(mmc->readreq->io->stream)) {
-							result = mmc_server_failure(mmc, mmc->readreq->io, "Read failed (socket was unexpectedly closed)", 0 TSRMLS_CC);
+							result = mmc_server_failure(mmc, mmc->readreq->io, "Read failed (socket was unexpectedly closed)", 0);
 							if (result == MMC_REQUEST_FAILURE) {
 								/* take server offline and failover requests */
-								mmc_server_deactivate(pool, mmc TSRMLS_CC);
+								mmc_server_deactivate(pool, mmc);
 							}
 						}
 						break;
@@ -1641,7 +1615,7 @@ void mmc_pool_select(mmc_pool_t *pool TS
 						break;
 
 					default:
-						php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid return value, bailing out");
+						php_error_docref(NULL, E_ERROR, "Invalid return value, bailing out");
 				}
 			} while (mmc->readreq != NULL && (result == MMC_REQUEST_DONE || result == MMC_REQUEST_AGAIN));
 
@@ -1660,23 +1634,23 @@ void mmc_pool_select(mmc_pool_t *pool TS
 }
 /* }}} */
 
-void mmc_pool_run(mmc_pool_t *pool TSRMLS_DC)  /*
+void mmc_pool_run(mmc_pool_t *pool)  /*
 	runs all scheduled requests to completion {{{ */
 {
 	mmc_t *mmc;
 	while ((mmc = mmc_queue_pop(&(pool->pending))) != NULL) {
 		pool->protocol->end_get(mmc->buildreq);
-		mmc_pool_schedule(pool, mmc, mmc->buildreq TSRMLS_CC);
+		mmc_pool_schedule(pool, mmc, mmc->buildreq);
 		mmc->buildreq = NULL;
 	}
 
 	while (pool->reading->len || pool->sending->len) {
-		mmc_pool_select(pool TSRMLS_CC);
+		mmc_pool_select(pool);
 	}
 }
 /* }}} */
 
-inline int mmc_prepare_key_ex(const char *key, unsigned int key_len, char *result, unsigned int *result_len)  /* {{{ */
+MMC_POOL_INLINE int mmc_prepare_key_ex(const char *key, unsigned int key_len, char *result, unsigned int *result_len)  /* {{{ */
 {
 	unsigned int i;
 	if (key_len == 0) {
@@ -1694,7 +1668,7 @@ inline int mmc_prepare_key_ex(const char
 }
 /* }}} */
 
-inline int mmc_prepare_key(zval *key, char *result, unsigned int *result_len)  /* {{{ */
+MMC_POOL_INLINE int mmc_prepare_key(zval *key, char *result, unsigned int *result_len)  /* {{{ */
 {
 	if (Z_TYPE_P(key) == IS_STRING) {
 		return mmc_prepare_key_ex(Z_STRVAL_P(key), Z_STRLEN_P(key), result, result_len);
