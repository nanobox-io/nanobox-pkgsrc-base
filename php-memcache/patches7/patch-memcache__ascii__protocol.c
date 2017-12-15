$NetBSD$

--- memcache_ascii_protocol.c.orig	2013-04-08 02:12:54.000000000 +0000
+++ memcache_ascii_protocol.c
@@ -24,7 +24,7 @@
 #endif
 
 #include "memcache_pool.h"
-#include "ext/standard/php_smart_str.h"
+#include "ext/standard/php_smart_string.h"
 
 typedef struct mmc_ascii_request {
 	mmc_request_t	base;							/* enable cast to mmc_request_t */
@@ -36,13 +36,13 @@ typedef struct mmc_ascii_request {
 	} value;
 } mmc_ascii_request_t;
 
-static int mmc_server_read_value(mmc_t *, mmc_request_t * TSRMLS_DC);
+static int mmc_server_read_value(mmc_t *, mmc_request_t *);
 
-static int mmc_stream_get_line(mmc_stream_t *io, char **line TSRMLS_DC) /* 
+static int mmc_stream_get_line(mmc_stream_t *io, char **line) /* 
 	attempts to read a line from server, returns the line size or 0 if no complete line was available {{{ */
 {
 	size_t returned_len = 0;
-	io->readline(io, io->input.value + io->input.idx, MMC_BUFFER_SIZE - io->input.idx, &returned_len TSRMLS_CC);
+	io->readline(io, io->input.value + io->input.idx, MMC_BUFFER_SIZE - io->input.idx, &returned_len);
 	io->input.idx += returned_len;
 	
 	if (io->input.idx && io->input.value[io->input.idx - 1] == '\n') {
@@ -98,65 +98,64 @@ static int mmc_request_check_response(co
 	return response;
 }
 
-static int mmc_request_parse_response(mmc_t *mmc, mmc_request_t *request TSRMLS_DC) /* 
+static int mmc_request_parse_response(mmc_t *mmc, mmc_request_t *request) /* 
 	reads a generic response header and delegates it to response_handler {{{ */
 {
 	char *line;
-	int line_len = mmc_stream_get_line(request->io, &line TSRMLS_CC);
+	int line_len = mmc_stream_get_line(request->io, &line);
 	
 	if (line_len > 0) {
 		int response = mmc_request_check_response(line, line_len);
-		return request->response_handler(mmc, request, response, line, line_len - (sizeof("\r\n")-1), request->response_handler_param TSRMLS_CC);
+		return request->response_handler(mmc, request, response, line, line_len - (sizeof("\r\n")-1), request->response_handler_param);
 	}
 	
 	return MMC_REQUEST_MORE;
 }
 /* }}}*/
 
-static int mmc_request_parse_mutate(mmc_t *mmc, mmc_request_t *request TSRMLS_DC) /* 
+static int mmc_request_parse_mutate(mmc_t *mmc, mmc_request_t *request) /* 
 	reads and parses the <long-value> response header {{{ */
 {
 	char *line;
 	int line_len;
 	
-	line_len = mmc_stream_get_line(request->io, &line TSRMLS_CC);
+	line_len = mmc_stream_get_line(request->io, &line);
 	if (line_len > 0) {
 		long lval;
-		zval *value;
+		zval value;
 
 		int response = mmc_request_check_response(line, line_len);
 		if (response != MMC_RESPONSE_UNKNOWN) {
-			return request->response_handler(mmc, request, response, line, line_len - (sizeof("\r\n")-1), request->response_handler_param TSRMLS_CC);
+			return request->response_handler(mmc, request, response, line, line_len - (sizeof("\r\n")-1), request->response_handler_param);
 		}
 
 		if (sscanf(line, "%lu", &lval) < 1) {
-			return mmc_server_failure(mmc, request->io, "Malformed VALUE header", 0 TSRMLS_CC);
+			return mmc_server_failure(mmc, request->io, "Malformed VALUE header", 0);
 		}
 	
-		MAKE_STD_ZVAL(value);
-		ZVAL_LONG(value, lval);
-		return request->value_handler(request->key, request->key_len, value, 0, 0, request->value_handler_param TSRMLS_CC);
+		ZVAL_LONG(&value, lval);
+		return request->value_handler(request->key, request->key_len, &value, 0, 0, request->value_handler_param);
 	}
 	
 	return MMC_REQUEST_MORE;
 }
 /* }}}*/
 
-static int mmc_request_parse_value(mmc_t *mmc, mmc_request_t *request TSRMLS_DC) /* 
+static int mmc_request_parse_value(mmc_t *mmc, mmc_request_t *request) /* 
 	reads and parses the VALUE <key> <flags> <size> <cas> response header and then reads the value body {{{ */
 {
 	char *line;
 	int line_len;
 	mmc_ascii_request_t *req = (mmc_ascii_request_t *)request;
 	
-	line_len = mmc_stream_get_line(request->io, &line TSRMLS_CC);
+	line_len = mmc_stream_get_line(request->io, &line);
 	if (line_len > 0) {
 		if (mmc_str_left(line, "END", line_len, sizeof("END")-1)) {
 			return MMC_REQUEST_DONE;
 		}
 		
 		if (sscanf(line, MMC_VALUE_HEADER, req->value.key, &(req->value.flags), &(req->value.length), &(req->value.cas)) < 3) {
-			return mmc_server_failure(mmc, request->io, "Malformed VALUE header", 0 TSRMLS_CC);
+			return mmc_server_failure(mmc, request->io, "Malformed VALUE header", 0);
 		}
 		
 		/* memory for data + \r\n */
@@ -173,12 +172,12 @@ static int mmc_request_parse_value(mmc_t
 }
 /* }}}*/
 
-static int mmc_server_read_value(mmc_t *mmc, mmc_request_t *request TSRMLS_DC) /* 
+static int mmc_server_read_value(mmc_t *mmc, mmc_request_t *request) /* 
 	read the value body into the buffer {{{ */
 {
 	mmc_ascii_request_t *req = (mmc_ascii_request_t *)request;
 	request->readbuf.idx += 
-		request->io->read(request->io, request->readbuf.value.c + request->readbuf.idx, req->value.length + 2 - request->readbuf.idx TSRMLS_CC);
+		request->io->read(request->io, request->readbuf.value.c + request->readbuf.idx, req->value.length + 2 - request->readbuf.idx);
 
 	/* done reading? */
 	if (request->readbuf.idx >= req->value.length + 2) {
@@ -190,7 +189,7 @@ static int mmc_server_read_value(mmc_t *
 
 		result = mmc_unpack_value(
 			mmc, request, &(request->readbuf), req->value.key, strlen(req->value.key), 
-			req->value.flags, req->value.cas, req->value.length TSRMLS_CC);
+			req->value.flags, req->value.cas, req->value.length);
 		
 		/* request more data (END line) */
 		if (result == MMC_REQUEST_DONE) {
@@ -207,7 +206,7 @@ static int mmc_server_read_value(mmc_t *
 static mmc_request_t *mmc_ascii_create_request() /* {{{ */ 
 {
 	mmc_ascii_request_t *request = emalloc(sizeof(mmc_ascii_request_t));
-	memset(request, 0, sizeof(*request));
+	ZEND_SECURE_ZERO(request, sizeof(*request));
 	return (mmc_request_t *)request;
 }
 /* }}} */
@@ -229,24 +228,24 @@ static void mmc_ascii_begin_get(mmc_requ
 	request->parse = mmc_request_parse_value;
 
 	if (op == MMC_OP_GETS) {
-		smart_str_appendl(&(request->sendbuf.value), "gets", sizeof("gets")-1);		
+		smart_string_appendl(&(request->sendbuf.value), "gets", sizeof("gets")-1);
 	}
 	else {
-		smart_str_appendl(&(request->sendbuf.value), "get", sizeof("get")-1);
+		smart_string_appendl(&(request->sendbuf.value), "get", sizeof("get")-1);
 	}
 }
 /* }}} */
 
 static void mmc_ascii_append_get(mmc_request_t *request, zval *zkey, const char *key, unsigned int key_len) /* {{{ */
 {
-	smart_str_appendl(&(request->sendbuf.value), " ", 1);
-	smart_str_appendl(&(request->sendbuf.value), key, key_len);
+	smart_string_appendl(&(request->sendbuf.value), " ", 1);
+	smart_string_appendl(&(request->sendbuf.value), key, key_len);
 }
 /* }}} */
 
 static void mmc_ascii_end_get(mmc_request_t *request) /* {{{ */ 
 {
-	smart_str_appendl(&(request->sendbuf.value), "\r\n", sizeof("\r\n")-1);
+	smart_string_appendl(&(request->sendbuf.value), "\r\n", sizeof("\r\n")-1);
 }
 /* }}} */
 
@@ -260,14 +259,14 @@ static void mmc_ascii_get(mmc_request_t
 
 static int mmc_ascii_store(
 	mmc_pool_t *pool, mmc_request_t *request, int op, const char *key, unsigned int key_len, 
-	unsigned int flags, unsigned int exptime, unsigned long cas, zval *value TSRMLS_DC) /* {{{ */ 
+	unsigned int flags, unsigned int exptime, unsigned long cas, zval *value) /* {{{ */ 
 {
 	int status;
 	mmc_buffer_t buffer;
 	request->parse = mmc_request_parse_response;
 
-	memset(&buffer, 0, sizeof(buffer));
-	status = mmc_pack_value(pool, &buffer, value, &flags TSRMLS_CC);
+	ZEND_SECURE_ZERO(&buffer, sizeof(buffer));
+	status = mmc_pack_value(pool, &buffer, value, &flags);
 	
 	if (status != MMC_OK) {
 		return status;
@@ -275,44 +274,44 @@ static int mmc_ascii_store(
 	
 	switch (op) {
 		case MMC_OP_SET:
-			smart_str_appendl(&(request->sendbuf.value), "set", sizeof("set")-1);
+			smart_string_appendl(&(request->sendbuf.value), "set", sizeof("set")-1);
 			break;
 		case MMC_OP_ADD:
-			smart_str_appendl(&(request->sendbuf.value), "add", sizeof("add")-1);
+			smart_string_appendl(&(request->sendbuf.value), "add", sizeof("add")-1);
 			break;
 		case MMC_OP_REPLACE:
-			smart_str_appendl(&(request->sendbuf.value), "replace", sizeof("replace")-1);
+			smart_string_appendl(&(request->sendbuf.value), "replace", sizeof("replace")-1);
 			break;
 		case MMC_OP_CAS:
-			smart_str_appendl(&(request->sendbuf.value), "cas", sizeof("cas")-1);
+			smart_string_appendl(&(request->sendbuf.value), "cas", sizeof("cas")-1);
 			break;
 		case MMC_OP_APPEND:
-			smart_str_appendl(&(request->sendbuf.value), "append", sizeof("append")-1);
+			smart_string_appendl(&(request->sendbuf.value), "append", sizeof("append")-1);
 			break;
 		case MMC_OP_PREPEND:
-			smart_str_appendl(&(request->sendbuf.value), "prepend", sizeof("prepend")-1);
+			smart_string_appendl(&(request->sendbuf.value), "prepend", sizeof("prepend")-1);
 			break;
 		default:
 			return MMC_REQUEST_FAILURE;
 	}
 	
-	smart_str_appendl(&(request->sendbuf.value), " ", 1);
-	smart_str_appendl(&(request->sendbuf.value), key, key_len);
-	smart_str_appendl(&(request->sendbuf.value), " ", 1);
-	smart_str_append_unsigned(&(request->sendbuf.value), flags);
-	smart_str_appendl(&(request->sendbuf.value), " ", 1);
-	smart_str_append_unsigned(&(request->sendbuf.value), exptime);
-	smart_str_appendl(&(request->sendbuf.value), " ", 1);
-	smart_str_append_unsigned(&(request->sendbuf.value), buffer.value.len);
+	smart_string_appendl(&(request->sendbuf.value), " ", 1);
+	smart_string_appendl(&(request->sendbuf.value), key, key_len);
+	smart_string_appendl(&(request->sendbuf.value), " ", 1);
+	smart_string_append_unsigned(&(request->sendbuf.value), flags);
+	smart_string_appendl(&(request->sendbuf.value), " ", 1);
+	smart_string_append_unsigned(&(request->sendbuf.value), exptime);
+	smart_string_appendl(&(request->sendbuf.value), " ", 1);
+	smart_string_append_unsigned(&(request->sendbuf.value), buffer.value.len);
 
 	if (op == MMC_OP_CAS) {
-		smart_str_appendl(&(request->sendbuf.value), " ", 1);
-		smart_str_append_unsigned(&(request->sendbuf.value), cas);
+		smart_string_appendl(&(request->sendbuf.value), " ", 1);
+		smart_string_append_unsigned(&(request->sendbuf.value), cas);
 	}
 	
-	smart_str_appendl(&(request->sendbuf.value), "\r\n", sizeof("\r\n")-1);
-	smart_str_appendl(&(request->sendbuf.value), buffer.value.c, buffer.value.len);
-	smart_str_appendl(&(request->sendbuf.value), "\r\n", sizeof("\r\n")-1);
+	smart_string_appendl(&(request->sendbuf.value), "\r\n", sizeof("\r\n")-1);
+	smart_string_appendl(&(request->sendbuf.value), buffer.value.c, buffer.value.len);
+	smart_string_appendl(&(request->sendbuf.value), "\r\n", sizeof("\r\n")-1);
 	
 	mmc_buffer_free(&buffer);	
 	return MMC_OK;
@@ -323,16 +322,16 @@ static void mmc_ascii_delete(mmc_request
 {
 	request->parse = mmc_request_parse_response;
 	
-	smart_str_appendl(&(request->sendbuf.value), "delete", sizeof("delete")-1);
-	smart_str_appendl(&(request->sendbuf.value), " ", 1);
-	smart_str_appendl(&(request->sendbuf.value), key, key_len);
+	smart_string_appendl(&(request->sendbuf.value), "delete", sizeof("delete")-1);
+	smart_string_appendl(&(request->sendbuf.value), " ", 1);
+	smart_string_appendl(&(request->sendbuf.value), key, key_len);
 	
 	if (exptime > 0) {
-		smart_str_appendl(&(request->sendbuf.value), " ", 1);
-		smart_str_append_unsigned(&(request->sendbuf.value), exptime);
+		smart_string_appendl(&(request->sendbuf.value), " ", 1);
+		smart_string_append_unsigned(&(request->sendbuf.value), exptime);
 	}
 
-	smart_str_appendl(&(request->sendbuf.value), "\r\n", sizeof("\r\n")-1);
+	smart_string_appendl(&(request->sendbuf.value), "\r\n", sizeof("\r\n")-1);
 }
 /* }}} */
 
@@ -341,38 +340,38 @@ static void mmc_ascii_mutate(mmc_request
 	request->parse = mmc_request_parse_mutate;
 	
 	if (value >= 0) {
-		smart_str_appendl(&(request->sendbuf.value), "incr", sizeof("incr")-1);
+		smart_string_appendl(&(request->sendbuf.value), "incr", sizeof("incr")-1);
 	}
 	else {
-		smart_str_appendl(&(request->sendbuf.value), "decr", sizeof("decr")-1);
+		smart_string_appendl(&(request->sendbuf.value), "decr", sizeof("decr")-1);
 	}
 	
-	smart_str_appendl(&(request->sendbuf.value), " ", 1);
-	smart_str_appendl(&(request->sendbuf.value), key, key_len);
-	smart_str_appendl(&(request->sendbuf.value), " ", 1);
-	smart_str_append_unsigned(&(request->sendbuf.value), value >= 0 ? value : -value);
-	smart_str_appendl(&(request->sendbuf.value), "\r\n", sizeof("\r\n")-1);
+	smart_string_appendl(&(request->sendbuf.value), " ", 1);
+	smart_string_appendl(&(request->sendbuf.value), key, key_len);
+	smart_string_appendl(&(request->sendbuf.value), " ", 1);
+	smart_string_append_unsigned(&(request->sendbuf.value), value >= 0 ? value : -value);
+	smart_string_appendl(&(request->sendbuf.value), "\r\n", sizeof("\r\n")-1);
 }
 /* }}} */
 
 static void mmc_ascii_flush(mmc_request_t *request, unsigned int exptime) /* {{{ */
 {
 	request->parse = mmc_request_parse_response;
-	smart_str_appendl(&(request->sendbuf.value), "flush_all", sizeof("flush_all")-1);
+	smart_string_appendl(&(request->sendbuf.value), "flush_all", sizeof("flush_all")-1);
 
 	if (exptime > 0) {
-		smart_str_appendl(&(request->sendbuf.value), " ", 1);
-		smart_str_append_unsigned(&(request->sendbuf.value), exptime);
+		smart_string_appendl(&(request->sendbuf.value), " ", 1);
+		smart_string_append_unsigned(&(request->sendbuf.value), exptime);
 	}
 
-	smart_str_appendl(&(request->sendbuf.value), "\r\n", sizeof("\r\n")-1);
+	smart_string_appendl(&(request->sendbuf.value), "\r\n", sizeof("\r\n")-1);
 }
 /* }}} */
 
 static void mmc_ascii_version(mmc_request_t *request) /* {{{ */ 
 {
 	request->parse = mmc_request_parse_response;
-	smart_str_appendl(&(request->sendbuf.value), "version\r\n", sizeof("version\r\n")-1);
+	smart_string_appendl(&(request->sendbuf.value), "version\r\n", sizeof("version\r\n")-1);
 }
 /* }}} */
 
@@ -392,11 +391,17 @@ static void mmc_ascii_stats(mmc_request_
 		cmd_len = spprintf(&cmd, 0, "stats\r\n");
 	}
 	
-	smart_str_appendl(&(request->sendbuf.value), cmd, cmd_len);
+	smart_string_appendl(&(request->sendbuf.value), cmd, cmd_len);
 	efree(cmd);
 }
 /* }}} */
 
+static void mmc_set_sasl_auth_data(mmc_pool_t *pool, mmc_request_t *request, const char *user,  const char *password) /* {{{ */
+{
+	/* stats not supported */
+}
+/* }}} */
+
 mmc_protocol_t mmc_ascii_protocol = {
 	mmc_ascii_create_request,
 	mmc_ascii_clone_request,
@@ -411,7 +416,8 @@ mmc_protocol_t mmc_ascii_protocol = {
 	mmc_ascii_mutate,
 	mmc_ascii_flush,
 	mmc_ascii_version,
-	mmc_ascii_stats
+	mmc_ascii_stats,
+	mmc_set_sasl_auth_data
 };
 
 /*
