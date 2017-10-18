$NetBSD$

--- memcache_binary_protocol.c.orig	2013-04-08 02:12:54.000000000 +0000
+++ memcache_binary_protocol.c
@@ -397,8 +397,8 @@ static void mmc_binary_append_get(mmc_re
 
 	/* reqid/opaque is the index into the collection of key pointers */  
 	mmc_pack_header(&header, MMC_OP_GETQ, req->keys.len, key_len, 0, 0);
-	smart_str_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));	
-	smart_str_appendl(&(request->sendbuf.value), key, key_len);
+	smart_string_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));	
+	smart_string_appendl(&(request->sendbuf.value), key, key_len);
 
 	/* store key to be used by the response handler */
 	mmc_queue_push(&(req->keys), zkey); 
@@ -410,7 +410,7 @@ static void mmc_binary_end_get(mmc_reque
 	mmc_request_header_t header;
 	mmc_binary_request_t *req = (mmc_binary_request_t *)request;
 	mmc_pack_header(&header, MMC_OP_NOOP, req->keys.len, 0, 0, 0);
-	smart_str_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));	
+	smart_string_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));	
 }
 /* }}} */
 
@@ -423,8 +423,8 @@ static void mmc_binary_get(mmc_request_t
 
 	/* reqid/opaque is the index into the collection of key pointers */  
 	mmc_pack_header(&header, MMC_OP_GET, req->keys.len, key_len, 0, 0);
-	smart_str_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));	
-	smart_str_appendl(&(request->sendbuf.value), key, key_len);
+	smart_string_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));	
+	smart_string_appendl(&(request->sendbuf.value), key, key_len);
 
 	/* store key to be used by the response handler */
 	mmc_queue_push(&(req->keys), zkey); 
@@ -449,7 +449,7 @@ static int mmc_binary_store(
 	request->sendbuf.value.len += sizeof(*header);
 	
 	/* append key and data */
-	smart_str_appendl(&(request->sendbuf.value), key, key_len);
+	smart_string_appendl(&(request->sendbuf.value), key, key_len);
 	
 	valuelen = request->sendbuf.value.len;
 	status = mmc_pack_value(pool, &(request->sendbuf), value, &flags TSRMLS_CC);
@@ -493,8 +493,8 @@ static void mmc_binary_delete(mmc_reques
 	mmc_pack_header(&(header.base), MMC_OP_DELETE, 0, key_len, sizeof(header) - sizeof(header.base), 0);
 	header.exptime = htonl(exptime);
 	
-	smart_str_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));	
-	smart_str_appendl(&(request->sendbuf.value), key, key_len);
+	smart_string_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));	
+	smart_string_appendl(&(request->sendbuf.value), key, key_len);
 }
 /* }}} */
 
@@ -526,8 +526,8 @@ static void mmc_binary_mutate(mmc_reques
 		header.exptime = ~(uint32_t)0;
 	}
 	
-	smart_str_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));	
-	smart_str_appendl(&(request->sendbuf.value), key, key_len);
+	smart_string_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));	
+	smart_string_appendl(&(request->sendbuf.value), key, key_len);
 
 	/* store key to be used by the response handler */
 	mmc_queue_push(&(req->keys), zkey); 
@@ -543,7 +543,7 @@ static void mmc_binary_flush(mmc_request
 	req->next_parse_handler = mmc_request_read_response;
 	
 	mmc_pack_header(&header, MMC_OP_FLUSH, 0, 0, 0, 0);
-	smart_str_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));	
+	smart_string_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));	
 }
 /* }}} */
 
@@ -556,7 +556,7 @@ static void mmc_binary_version(mmc_reque
 	req->next_parse_handler = mmc_request_read_response;
 	
 	mmc_pack_header(&header, MMC_OP_VERSION, 0, 0, 0, 0);
-	smart_str_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));	
+	smart_string_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));	
 }
 /* }}} */
 
@@ -570,7 +570,7 @@ static void mmc_binary_stats(mmc_request
 	req->next_parse_handler = mmc_request_read_response;
 	
 	mmc_pack_header(&header, MMC_OP_NOOP, 0, 0, 0, 0);
-	smart_str_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));	
+	smart_string_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));	
 }
 /* }}} */
 
