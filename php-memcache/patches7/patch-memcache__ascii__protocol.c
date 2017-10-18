$NetBSD$

--- memcache_ascii_protocol.c.orig	2013-04-08 02:12:54.000000000 +0000
+++ memcache_ascii_protocol.c
@@ -229,24 +229,24 @@ static void mmc_ascii_begin_get(mmc_requ
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
 
@@ -275,44 +275,44 @@ static int mmc_ascii_store(
 	
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
@@ -323,16 +323,16 @@ static void mmc_ascii_delete(mmc_request
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
 
@@ -341,38 +341,38 @@ static void mmc_ascii_mutate(mmc_request
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
 
@@ -392,7 +392,7 @@ static void mmc_ascii_stats(mmc_request_
 		cmd_len = spprintf(&cmd, 0, "stats\r\n");
 	}
 	
-	smart_str_appendl(&(request->sendbuf.value), cmd, cmd_len);
+	smart_string_appendl(&(request->sendbuf.value), cmd, cmd_len);
 	efree(cmd);
 }
 /* }}} */
