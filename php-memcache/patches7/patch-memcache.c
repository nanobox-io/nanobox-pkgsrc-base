$NetBSD$

--- memcache.c.orig	2013-04-08 02:12:54.000000000 +0000
+++ memcache.c
@@ -29,10 +29,6 @@
 #include "ext/standard/php_string.h"
 #include "php_memcache.h"
 
-#ifndef ZEND_ENGINE_2
-#define OnUpdateLong OnUpdateInt
-#endif
-
 /* True global resources - no need for thread safety here */
 static int le_memcache_pool, le_memcache_server;
 static zend_class_entry *memcache_pool_ce;
@@ -42,6 +38,19 @@ ZEND_EXTERN_MODULE_GLOBALS(memcache)
 
 /* {{{ memcache_functions[]
  */
+ZEND_BEGIN_ARG_INFO(arginfo_memcache_get, 1)
+	ZEND_ARG_PASS_INFO(0)
+	ZEND_ARG_PASS_INFO(0)
+	ZEND_ARG_PASS_INFO(1)
+	ZEND_ARG_PASS_INFO(1)
+ZEND_END_ARG_INFO()
+
+ZEND_BEGIN_ARG_INFO(arginfo_memcache_object_get, 1)
+	ZEND_ARG_PASS_INFO(0)
+	ZEND_ARG_PASS_INFO(1)
+	ZEND_ARG_PASS_INFO(1)
+ZEND_END_ARG_INFO()
+
 zend_function_entry memcache_functions[] = {
 	PHP_FE(memcache_connect,				NULL)
 	PHP_FE(memcache_pconnect,				NULL)
@@ -56,7 +65,7 @@ zend_function_entry memcache_functions[]
 	PHP_FE(memcache_cas,					NULL)
 	PHP_FE(memcache_append,					NULL)
 	PHP_FE(memcache_prepend,				NULL)
-	PHP_FE(memcache_get,					NULL)
+	PHP_FE(memcache_get,					arginfo_memcache_get)
 	PHP_FE(memcache_delete,					NULL)
 	PHP_FE(memcache_debug,					NULL)
 	PHP_FE(memcache_get_stats,				NULL)
@@ -66,6 +75,7 @@ zend_function_entry memcache_functions[]
 	PHP_FE(memcache_decrement,				NULL)
 	PHP_FE(memcache_close,					NULL)
 	PHP_FE(memcache_flush,					NULL)
+	PHP_FE(memcache_set_sasl_auth_data,		NULL)
 	{NULL, NULL, NULL}
 };
 
@@ -83,7 +93,7 @@ static zend_function_entry php_memcache_
 	PHP_FALIAS(cas,						memcache_cas,						NULL)
 	PHP_FALIAS(append,					memcache_append,					NULL)
 	PHP_FALIAS(prepend,					memcache_prepend,					NULL)
-	PHP_FALIAS(get,						memcache_get,						NULL)
+	PHP_FALIAS(get,						memcache_get,						arginfo_memcache_object_get)
 	PHP_FALIAS(delete,					memcache_delete,					NULL)
 	PHP_FALIAS(getstats,				memcache_get_stats,					NULL)
 	PHP_FALIAS(getextendedstats,		memcache_get_extended_stats,		NULL)
@@ -92,6 +102,8 @@ static zend_function_entry php_memcache_
 	PHP_FALIAS(decrement,				memcache_decrement,					NULL)
 	PHP_FALIAS(close,					memcache_close,						NULL)
 	PHP_FALIAS(flush,					memcache_flush,						NULL)
+	PHP_FALIAS(setSaslAuthData,			memcache_set_sasl_auth_data,				NULL)
+
 	{NULL, NULL, NULL}
 };
 
@@ -107,9 +119,7 @@ static zend_function_entry php_memcache_
 /* {{{ memcache_module_entry
  */
 zend_module_entry memcache_module_entry = {
-#if ZEND_MODULE_API_NO >= 20010901
 	STANDARD_MODULE_HEADER,
-#endif
 	"memcache",
 	memcache_functions,
 	PHP_MINIT(memcache),
@@ -117,9 +127,7 @@ zend_module_entry memcache_module_entry
 	NULL,
 	NULL,
 	PHP_MINFO(memcache),
-#if ZEND_MODULE_API_NO >= 20010901
 	PHP_MEMCACHE_VERSION,
-#endif
 	STANDARD_MODULE_PROPERTIES
 };
 /* }}} */
@@ -130,42 +138,44 @@ ZEND_GET_MODULE(memcache)
 
 static PHP_INI_MH(OnUpdateChunkSize) /* {{{ */
 {
-	long int lval;
+	zend_long val;
+	char *endptr = NULL;
 
-	lval = strtol(new_value, NULL, 10);
-	if (lval <= 0) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "memcache.chunk_size must be a positive integer ('%s' given)", new_value);
+	val = ZEND_STRTOL(ZSTR_VAL(new_value), &endptr, 10);
+	if (!endptr || (*endptr != '\0') || val <= 0) {
+		php_error_docref(NULL, E_WARNING, "memcache.chunk_size must be a positive integer ('%s' given)", ZSTR_VAL(new_value));
 		return FAILURE;
 	}
 
-	return OnUpdateLong(entry, new_value, new_value_length, mh_arg1, mh_arg2, mh_arg3, stage TSRMLS_CC);
+	return OnUpdateLong(entry, new_value, mh_arg1, mh_arg2, mh_arg3, stage);
 }
 /* }}} */
 
 static PHP_INI_MH(OnUpdateFailoverAttempts) /* {{{ */
 {
-	long int lval;
+	zend_long val;
+	char *endptr = NULL;
 
-	lval = strtol(new_value, NULL, 10);
-	if (lval <= 0) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "memcache.max_failover_attempts must be a positive integer ('%s' given)", new_value);
+	val = ZEND_STRTOL(ZSTR_VAL(new_value), &endptr, 10);
+	if (!endptr || (*endptr != '\0') || val <= 0) {
+		php_error_docref(NULL, E_WARNING, "memcache.max_failover_attempts must be a positive integer ('%s' given)", ZSTR_VAL(new_value));
 		return FAILURE;
 	}
 
-	return OnUpdateLong(entry, new_value, new_value_length, mh_arg1, mh_arg2, mh_arg3, stage TSRMLS_CC);
+	return OnUpdateLong(entry, new_value, mh_arg1, mh_arg2, mh_arg3, stage);
 }
 /* }}} */
 
 static PHP_INI_MH(OnUpdateProtocol) /* {{{ */
 {
-	if (!strcasecmp(new_value, "ascii")) {
+	if (!strcasecmp(ZSTR_VAL(new_value), "ascii")) {
 		MEMCACHE_G(protocol) = MMC_ASCII_PROTOCOL;
 	}
-	else if (!strcasecmp(new_value, "binary")) {
+	else if (!strcasecmp(ZSTR_VAL(new_value), "binary")) {
 		MEMCACHE_G(protocol) = MMC_BINARY_PROTOCOL;
 	}
 	else {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "memcache.protocol must be in set {ascii, binary} ('%s' given)", new_value);
+		php_error_docref(NULL, E_WARNING, "memcache.protocol must be in set {ascii, binary} ('%s' given)", ZSTR_VAL(new_value));
 		return FAILURE;
 	}
 
@@ -175,14 +185,14 @@ static PHP_INI_MH(OnUpdateProtocol) /* {
 
 static PHP_INI_MH(OnUpdateHashStrategy) /* {{{ */
 {
-	if (!strcasecmp(new_value, "standard")) {
+	if (!strcasecmp(ZSTR_VAL(new_value), "standard")) {
 		MEMCACHE_G(hash_strategy) = MMC_STANDARD_HASH;
 	}
-	else if (!strcasecmp(new_value, "consistent")) {
+	else if (!strcasecmp(ZSTR_VAL(new_value), "consistent")) {
 		MEMCACHE_G(hash_strategy) = MMC_CONSISTENT_HASH;
 	}
 	else {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "memcache.hash_strategy must be in set {standard, consistent} ('%s' given)", new_value);
+		php_error_docref(NULL, E_WARNING, "memcache.hash_strategy must be in set {standard, consistent} ('%s' given)", ZSTR_VAL(new_value));
 		return FAILURE;
 	}
 
@@ -192,14 +202,14 @@ static PHP_INI_MH(OnUpdateHashStrategy)
 
 static PHP_INI_MH(OnUpdateHashFunction) /* {{{ */
 {
-	if (!strcasecmp(new_value, "crc32")) {
+	if (!strcasecmp(ZSTR_VAL(new_value), "crc32")) {
 		MEMCACHE_G(hash_function) = MMC_HASH_CRC32;
 	}
-	else if (!strcasecmp(new_value, "fnv")) {
+	else if (!strcasecmp(ZSTR_VAL(new_value), "fnv")) {
 		MEMCACHE_G(hash_function) = MMC_HASH_FNV1A;
 	}
 	else {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "memcache.hash_function must be in set {crc32, fnv} ('%s' given)", new_value);
+		php_error_docref(NULL, E_WARNING, "memcache.hash_function must be in set {crc32, fnv} ('%s' given)", ZSTR_VAL(new_value));
 		return FAILURE;
 	}
 
@@ -209,43 +219,46 @@ static PHP_INI_MH(OnUpdateHashFunction)
 
 static PHP_INI_MH(OnUpdateRedundancy) /* {{{ */
 {
-	long int lval;
+	zend_long val;
+	char *endptr = NULL;
 
-	lval = strtol(new_value, NULL, 10);
-	if (lval <= 0) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "memcache.redundancy must be a positive integer ('%s' given)", new_value);
+	val = ZEND_STRTOL(ZSTR_VAL(new_value), &endptr, 10);
+	if (!endptr || (*endptr != '\0') || val <= 0) {
+		php_error_docref(NULL, E_WARNING, "memcache.redundancy must be a positive integer ('%s' given)", ZSTR_VAL(new_value));
 		return FAILURE;
 	}
 
-	return OnUpdateLong(entry, new_value, new_value_length, mh_arg1, mh_arg2, mh_arg3, stage TSRMLS_CC);
+	return OnUpdateLong(entry, new_value, mh_arg1, mh_arg2, mh_arg3, stage);
 }
 /* }}} */
 
 static PHP_INI_MH(OnUpdateCompressThreshold) /* {{{ */
 {
-	long int lval;
+	zend_long val;
+	char *endptr = NULL;
 
-	lval = strtol(new_value, NULL, 10);
-	if (lval < 0) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "memcache.compress_threshold must be a positive integer ('%s' given)", new_value);
+	val = ZEND_STRTOL(ZSTR_VAL(new_value), &endptr, 10);
+	if (!endptr || (*endptr != '\0') || val < 0) {
+		php_error_docref(NULL, E_WARNING, "memcache.compress_threshold must be a positive integer ('%s' given)", ZSTR_VAL(new_value));
 		return FAILURE;
 	}
 
-	return OnUpdateLong(entry, new_value, new_value_length, mh_arg1, mh_arg2, mh_arg3, stage TSRMLS_CC);
+	return OnUpdateLong(entry, new_value, mh_arg1, mh_arg2, mh_arg3, stage);
 }
 /* }}} */
 
 static PHP_INI_MH(OnUpdateLockTimeout) /* {{{ */
 {
-	long int lval;
+	zend_long val;
+	char *endptr = NULL;
 
-	lval = strtol(new_value, NULL, 10);
-	if (lval <= 0) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "memcache.lock_timeout must be a positive integer ('%s' given)", new_value);
+	val = ZEND_STRTOL(ZSTR_VAL(new_value), &endptr, 10);
+	if (!endptr || (*endptr != '\0') || val <= 0) {
+		php_error_docref(NULL, E_WARNING, "memcache.lock_timeout must be a positive integer ('%s' given)", ZSTR_VAL(new_value));
 		return FAILURE;
 	}
 
-	return OnUpdateLong(entry, new_value, new_value_length, mh_arg1, mh_arg2, mh_arg3, stage TSRMLS_CC);
+	return OnUpdateLong(entry, new_value, mh_arg1, mh_arg2, mh_arg3, stage);
 }
 /* }}} */
 
@@ -266,15 +279,15 @@ PHP_INI_END()
 /* }}} */
 
 /* {{{ internal function protos */
-static void _mmc_pool_list_dtor(zend_rsrc_list_entry * TSRMLS_DC);
-static void _mmc_server_list_dtor(zend_rsrc_list_entry * TSRMLS_DC);
-static void php_mmc_set_failure_callback(mmc_pool_t *, zval *, zval * TSRMLS_DC);
-static void php_mmc_failure_callback(mmc_pool_t *, mmc_t *, void * TSRMLS_DC);
+static void _mmc_pool_list_dtor(zend_resource*);
+static void _mmc_server_list_dtor(zend_resource*);
+static void php_mmc_set_failure_callback(mmc_pool_t *, zval *, zval *);
+static void php_mmc_failure_callback(mmc_pool_t *, mmc_t *, zval *);
 /* }}} */
 
 /* {{{ php_memcache_init_globals()
 */
-static void php_memcache_init_globals(zend_memcache_globals *memcache_globals_p TSRMLS_DC)
+static void php_memcache_init_globals(zend_memcache_globals *memcache_globals_p)
 {
 	MEMCACHE_G(hash_strategy)	  = MMC_STANDARD_HASH;
 	MEMCACHE_G(hash_function)	  = MMC_HASH_CRC32;
@@ -288,10 +301,10 @@ PHP_MINIT_FUNCTION(memcache)
 	zend_class_entry ce;
 
 	INIT_CLASS_ENTRY(ce, "MemcachePool", php_memcache_pool_class_functions);
-	memcache_pool_ce = zend_register_internal_class(&ce TSRMLS_CC);
+	memcache_pool_ce = zend_register_internal_class(&ce);
 
 	INIT_CLASS_ENTRY(ce, "Memcache", php_memcache_class_functions);
-	memcache_ce = zend_register_internal_class_ex(&ce, memcache_pool_ce, NULL TSRMLS_CC);
+	memcache_ce = zend_register_internal_class_ex(&ce, memcache_pool_ce);
 
 	le_memcache_pool = zend_register_list_destructors_ex(_mmc_pool_list_dtor, NULL, "memcache connection", module_number);
 	le_memcache_server = zend_register_list_destructors_ex(NULL, _mmc_server_list_dtor, "persistent memcache connection", module_number);
@@ -299,14 +312,14 @@ PHP_MINIT_FUNCTION(memcache)
 #ifdef ZTS
 	ts_allocate_id(&memcache_globals_id, sizeof(zend_memcache_globals), (ts_allocate_ctor) php_memcache_init_globals, NULL);
 #else
-	php_memcache_init_globals(&memcache_globals TSRMLS_CC);
+	php_memcache_init_globals(&memcache_globals);
 #endif
 
 	REGISTER_LONG_CONSTANT("MEMCACHE_COMPRESSED", MMC_COMPRESSED, CONST_CS | CONST_PERSISTENT);
-    REGISTER_LONG_CONSTANT("MEMCACHE_USER1", MMC_RESERVED_APPLICATIONDEFINEDFLAG_12, CONST_CS | CONST_PERSISTENT);
-    REGISTER_LONG_CONSTANT("MEMCACHE_USER2", MMC_RESERVED_APPLICATIONDEFINEDFLAG_13, CONST_CS | CONST_PERSISTENT);
-    REGISTER_LONG_CONSTANT("MEMCACHE_USER3", MMC_RESERVED_APPLICATIONDEFINEDFLAG_14, CONST_CS | CONST_PERSISTENT);
-    REGISTER_LONG_CONSTANT("MEMCACHE_USER4", MMC_RESERVED_APPLICATIONDEFINEDFLAG_15, CONST_CS | CONST_PERSISTENT);
+	REGISTER_LONG_CONSTANT("MEMCACHE_USER1", MMC_RESERVED_APPLICATIONDEFINEDFLAG_12, CONST_CS | CONST_PERSISTENT);
+	REGISTER_LONG_CONSTANT("MEMCACHE_USER2", MMC_RESERVED_APPLICATIONDEFINEDFLAG_13, CONST_CS | CONST_PERSISTENT);
+	REGISTER_LONG_CONSTANT("MEMCACHE_USER3", MMC_RESERVED_APPLICATIONDEFINEDFLAG_14, CONST_CS | CONST_PERSISTENT);
+	REGISTER_LONG_CONSTANT("MEMCACHE_USER4", MMC_RESERVED_APPLICATIONDEFINEDFLAG_15, CONST_CS | CONST_PERSISTENT);
 	REGISTER_INI_ENTRIES();
 
 #if HAVE_MEMCACHE_SESSION
@@ -347,46 +360,44 @@ PHP_MINFO_FUNCTION(memcache)
    internal functions
    ------------------ */
 
-static void _mmc_pool_list_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC) /* {{{ */
+static void _mmc_pool_list_dtor(zend_resource *rsrc) /* {{{ */
 {
 	mmc_pool_t *pool = (mmc_pool_t *)rsrc->ptr;
 
-	if (pool->failure_callback_param) {
-		zval_ptr_dtor((zval **)&pool->failure_callback_param);
-		pool->failure_callback_param = NULL;
+	if (!Z_ISUNDEF(pool->failure_callback_param)) {
+		Z_DELREF(pool->failure_callback_param);
+		ZVAL_UNDEF(&pool->failure_callback_param);
 	}
 
-	mmc_pool_free(pool TSRMLS_CC);
+	mmc_pool_free(pool);
 }
 /* }}} */
 
-static void _mmc_server_list_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC) /* {{{ */
+static void _mmc_server_list_dtor(zend_resource *rsrc) /* {{{ */
 {
-	mmc_server_free((mmc_t *)rsrc->ptr TSRMLS_CC);
+	mmc_server_free((mmc_t *)rsrc->ptr);
 }
 /* }}} */
 
-static int mmc_get_pool(zval *id, mmc_pool_t **pool TSRMLS_DC) /* {{{ */
+static int mmc_get_pool(zval *id, mmc_pool_t **pool) /* {{{ */
 {
-	zval **connection;
-	int resource_type;
+	zval *zv;
 
-	if (Z_TYPE_P(id) != IS_OBJECT || zend_hash_find(Z_OBJPROP_P(id), "connection", sizeof("connection"), (void **)&connection) == FAILURE) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "No servers added to memcache connection");
+	if (Z_TYPE_P(id) != IS_OBJECT || (zv = zend_hash_str_find(Z_OBJPROP_P(id), "connection", sizeof("connection")-1)) == NULL) {
+		php_error_docref(NULL, E_WARNING, "No servers added to memcache connection");
 		return 0;
 	}
 
-	*pool = (mmc_pool_t *) zend_list_find(Z_LVAL_PP(connection), &resource_type);
-	if (!*pool || resource_type != le_memcache_pool) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid MemcachePool->connection member variable");
-		return 0;
+	if (Z_TYPE_P(zv) != IS_RESOURCE || (*pool = zend_fetch_resource_ex(zv, "connection", le_memcache_pool)) == NULL) {
+			php_error_docref(NULL, E_WARNING, "Invalid MemcachePool->connection member variable");
+			return 0;
 	}
 
-	return Z_LVAL_PP(connection);
+	return 1;
 }
 /* }}} */
 
-int mmc_stored_handler(mmc_t *mmc, mmc_request_t *request, int response, const char *message, unsigned int message_len, void *param TSRMLS_DC) /*
+int mmc_stored_handler(mmc_t *mmc, mmc_request_t *request, int response, const char *message, unsigned int message_len, void *param) /*
 	handles SET/ADD/REPLACE response, param is a zval pointer to store result into {{{ */
 {
 	zval *result = (zval *)param;
@@ -400,20 +411,20 @@ int mmc_stored_handler(mmc_t *mmc, mmc_r
 	}
 
 	/* return FALSE or catch memory errors without failover */
-	if (response == MMC_RESPONSE_EXISTS || response == MMC_RESPONSE_OUT_OF_MEMORY || response == MMC_RESPONSE_TOO_LARGE 
+	if (response == MMC_RESPONSE_EXISTS || response == MMC_RESPONSE_OUT_OF_MEMORY || response == MMC_RESPONSE_TOO_LARGE
 			|| response == MMC_RESPONSE_CLIENT_ERROR) {
 		ZVAL_FALSE(result);
 
 		if (response != MMC_RESPONSE_EXISTS) {
 			/* trigger notice but no need for failover */
-			php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Server %s (tcp %d, udp %d) failed with: %s (%d)",
+			php_error_docref(NULL, E_NOTICE, "Server %s (tcp %d, udp %d) failed with: %s (%d)",
 				mmc->host, mmc->tcp.port, mmc->udp.port, message, response);
 		}
 
 		return MMC_REQUEST_DONE;
 	}
 
-	return mmc_request_failure(mmc, request->io, message, message_len, 0 TSRMLS_CC);
+	return mmc_request_failure(mmc, request->io, message, message_len, 0);
 }
 /* }}} */
 
@@ -422,98 +433,88 @@ static void php_mmc_store(INTERNAL_FUNCT
 	mmc_pool_t *pool;
 	mmc_request_t *request;
 	zval *keys, *value = 0, *mmc_object = getThis();
-	long flags = 0, exptime = 0, cas = 0;
+	zend_long flags = 0, exptime = 0, cas = 0;
 
 	if (mmc_object == NULL) {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Oz|zlll", &mmc_object, memcache_pool_ce, &keys, &value, &flags, &exptime, &cas) == FAILURE) {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "Oz|zlll", &mmc_object, memcache_pool_ce, &keys, &value, &flags, &exptime, &cas) == FAILURE) {
 			return;
 		}
 	}
 	else {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|zlll", &keys, &value, &flags, &exptime, &cas) == FAILURE) {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "z|zlll", &keys, &value, &flags, &exptime, &cas) == FAILURE) {
 			return;
 		}
 	}
 
-	if (!mmc_get_pool(mmc_object, &pool TSRMLS_CC) || !pool->num_servers) {
+	if (!mmc_get_pool(mmc_object, &pool) || !pool->num_servers) {
 		RETURN_FALSE;
 	}
 
 	RETVAL_NULL();
 
 	if (Z_TYPE_P(keys) == IS_ARRAY) {
-		zstr key;
-		char keytmp[MAX_LENGTH_OF_LONG + 1];
-		unsigned int key_len;
-		unsigned long index;
-		int key_type;
-
-		zval **arrval;
-		HashPosition pos;
-		zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(keys), &pos);
-
-		while (zend_hash_get_current_data_ex(Z_ARRVAL_P(keys), (void **)&arrval, &pos) == SUCCESS) {
-			key_type = zend_hash_get_current_key_ex(Z_ARRVAL_P(keys), &key, &key_len, &index, 0, &pos);
-			zend_hash_move_forward_ex(Z_ARRVAL_P(keys), &pos);
-
-			switch (key_type) {
-				case HASH_KEY_IS_STRING:
-					key_len--;
-					break;
-
-				case HASH_KEY_IS_LONG:
-					key_len = sprintf(keytmp, "%lu", index);
-					key = ZSTR(keytmp);
-					break;
-
-				default:
-					php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid key");
-					continue;
+		zend_string *key;
+		zval *val;
+		zend_ulong index;
+
+		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(keys), index, key, val ) {
+			zend_string *str_key = NULL;
+			if (key == NULL) {
+				str_key = strpprintf(0, ZEND_ULONG_FMT, index);
+			} else {
+				str_key = key;
 			}
 
 			/* allocate request */
 			request = mmc_pool_request(pool, MMC_PROTO_TCP,
-				mmc_stored_handler, return_value, mmc_pool_failover_handler, NULL TSRMLS_CC);
+					mmc_stored_handler, return_value, mmc_pool_failover_handler, NULL);
 
-			if (mmc_prepare_key_ex(ZSTR_VAL(key), key_len, request->key, &(request->key_len)) != MMC_OK) {
-				php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid key");
+			if (mmc_prepare_key_ex(ZSTR_VAL(str_key), ZSTR_LEN(str_key), request->key, &(request->key_len)) != MMC_OK) {
+				php_error_docref(NULL, E_WARNING, "Invalid key");
 				mmc_pool_release(pool, request);
+				if (key == NULL) {
+					zend_string_release(str_key);
+				}
 				continue;
 			}
 
+			if (key == NULL) {
+				zend_string_release(str_key);
+			}
+
 			/* assemble command */
-			if (pool->protocol->store(pool, request, op, request->key, request->key_len, flags, exptime, cas, *arrval TSRMLS_CC) != MMC_OK) {
+			if (pool->protocol->store(pool, request, op, request->key, request->key_len, flags, exptime, cas, val) != MMC_OK) {
 				mmc_pool_release(pool, request);
 				continue;
 			}
 
 			/* schedule request */
-			if (mmc_pool_schedule_key(pool, request->key, request->key_len, request, MEMCACHE_G(redundancy) TSRMLS_CC) != MMC_OK) {
+			if (mmc_pool_schedule_key(pool, request->key, request->key_len, request, MEMCACHE_G(redundancy)) != MMC_OK) {
 				continue;
 			}
 
 			/* begin sending requests immediatly */
-			mmc_pool_select(pool TSRMLS_CC);
-		}
+			mmc_pool_select(pool);
+		} ZEND_HASH_FOREACH_END();
 	}
 	else if (value) {
 		/* allocate request */
-		request = mmc_pool_request(pool, MMC_PROTO_TCP, mmc_stored_handler, return_value, mmc_pool_failover_handler, NULL TSRMLS_CC);
+		request = mmc_pool_request(pool, MMC_PROTO_TCP, mmc_stored_handler, return_value, mmc_pool_failover_handler, NULL);
 
 		if (mmc_prepare_key(keys, request->key, &(request->key_len)) != MMC_OK) {
-			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid key");
+			php_error_docref(NULL, E_WARNING, "Invalid key");
 			mmc_pool_release(pool, request);
 			RETURN_FALSE;
 		}
 
 		/* assemble command */
-		if (pool->protocol->store(pool, request, op, request->key, request->key_len, flags, exptime, cas, value TSRMLS_CC) != MMC_OK) {
+		if (pool->protocol->store(pool, request, op, request->key, request->key_len, flags, exptime, cas, value) != MMC_OK) {
 			mmc_pool_release(pool, request);
 			RETURN_FALSE;
 		}
 
 		/* schedule request */
-		if (mmc_pool_schedule_key(pool, request->key, request->key_len, request, MEMCACHE_G(redundancy) TSRMLS_CC) != MMC_OK) {
+		if (mmc_pool_schedule_key(pool, request->key, request->key_len, request, MEMCACHE_G(redundancy)) != MMC_OK) {
 			RETURN_FALSE;
 		}
 	}
@@ -522,7 +523,7 @@ static void php_mmc_store(INTERNAL_FUNCT
 	}
 
 	/* execute all requests */
-	mmc_pool_run(pool TSRMLS_CC);
+	mmc_pool_run(pool);
 
 	if (Z_TYPE_P(return_value) == IS_NULL) {
 		RETVAL_FALSE;
@@ -530,7 +531,7 @@ static void php_mmc_store(INTERNAL_FUNCT
 }
 /* }}} */
 
-int mmc_numeric_response_handler(mmc_t *mmc, mmc_request_t *request, int response, const char *message, unsigned int message_len, void *param TSRMLS_DC) /*
+int mmc_numeric_response_handler(mmc_t *mmc, mmc_request_t *request, int response, const char *message, unsigned int message_len, void *param) /*
 	handles a mutate response line, param is a zval pointer to store result into {{{ */
 {
 	zval *result = (zval *)param;
@@ -556,16 +557,16 @@ int mmc_numeric_response_handler(mmc_t *
 		}
 
 		if (response != MMC_RESPONSE_NOT_FOUND) {
-			php_error_docref(NULL TSRMLS_CC, 
+			php_error_docref(NULL,
 					E_NOTICE, "Server %s (tcp %d, udp %d) failed with: %s (%d)",
-					mmc->host, mmc->tcp.port, 
+					mmc->host, mmc->tcp.port,
 					mmc->udp.port, message, response);
 		}
 
 		return MMC_REQUEST_DONE;
 	}
 
-	return mmc_request_failure(mmc, request->io, message, message_len, 0 TSRMLS_CC);
+	return mmc_request_failure(mmc, request->io, message, message_len, 0);
 }
 /* }}} */
 
@@ -576,19 +577,19 @@ static void php_mmc_numeric(INTERNAL_FUN
 	zval *mmc_object = getThis();
 
 	zval *keys;
-	long value = 1, defval = 0, exptime = 0;
+	zend_long value = 1, defval = 0, exptime = 0;
 	mmc_request_t *request;
 	void *value_handler_param[3];
 	int defval_used = 0;
 
 	if (mmc_object == NULL) {
 		if (deleted) {
-			if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Oz|l", &mmc_object, memcache_pool_ce, &keys, &value) == FAILURE) {
+			if (zend_parse_parameters(ZEND_NUM_ARGS(), "Oz|l", &mmc_object, memcache_pool_ce, &keys, &value) == FAILURE) {
 				return;
 			}
 		}
 		else {
-			if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Oz|lll", &mmc_object, memcache_pool_ce, &keys, &value, &defval, &exptime) == FAILURE) {
+			if (zend_parse_parameters(ZEND_NUM_ARGS(), "Oz|lll", &mmc_object, memcache_pool_ce, &keys, &value, &defval, &exptime) == FAILURE) {
 				return;
 			}
 
@@ -597,12 +598,12 @@ static void php_mmc_numeric(INTERNAL_FUN
 	}
 	else {
 		if (deleted) {
-			if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|l", &keys, &value) == FAILURE) {
+			if (zend_parse_parameters(ZEND_NUM_ARGS(), "z|l", &keys, &value) == FAILURE) {
 				return;
 			}
 		}
 		else {
-			if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|lll", &keys, &value, &defval, &exptime) == FAILURE) {
+			if (zend_parse_parameters(ZEND_NUM_ARGS(), "z|lll", &keys, &value, &defval, &exptime) == FAILURE) {
 				return;
 			}
 
@@ -610,7 +611,7 @@ static void php_mmc_numeric(INTERNAL_FUN
 		}
 	}
 
-	if (!mmc_get_pool(mmc_object, &pool TSRMLS_CC) || !pool->num_servers) {
+	if (!mmc_get_pool(mmc_object, &pool) || !pool->num_servers) {
 		RETURN_FALSE;
 	}
 
@@ -619,8 +620,8 @@ static void php_mmc_numeric(INTERNAL_FUN
 	value_handler_param[2] = NULL;
 
 	if (Z_TYPE_P(keys) == IS_ARRAY) {
-		zval **key;
-		HashPosition pos;
+		zval *key;
+		zend_ulong key_index;
 
 		if (deleted) {
 			/* changed to true/false by mmc_numeric_response_handler */
@@ -631,21 +632,18 @@ static void php_mmc_numeric(INTERNAL_FUN
 			array_init(return_value);
 		}
 
-		zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(keys), &pos);
-		while (zend_hash_get_current_data_ex(Z_ARRVAL_P(keys), (void **)&key, &pos) == SUCCESS) {
-			zend_hash_move_forward_ex(Z_ARRVAL_P(keys), &pos);
-
+		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(keys), key) {
 			/* allocate request */
 			request = mmc_pool_request(
-				pool, MMC_PROTO_TCP, mmc_numeric_response_handler, return_value,
-				mmc_pool_failover_handler, NULL TSRMLS_CC);
+					pool, MMC_PROTO_TCP, mmc_numeric_response_handler, return_value,
+					mmc_pool_failover_handler, NULL);
 
 			request->value_handler = mmc_value_handler_multi;
 			request->value_handler_param = value_handler_param;
 
-			if (mmc_prepare_key(*key, request->key, &(request->key_len)) != MMC_OK) {
+			if (mmc_prepare_key(key, request->key, &(request->key_len)) != MMC_OK) {
 				mmc_pool_release(pool, request);
-				php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid key");
+				php_error_docref(NULL, E_WARNING, "Invalid key");
 				continue;
 			}
 
@@ -653,17 +651,18 @@ static void php_mmc_numeric(INTERNAL_FUN
 				pool->protocol->delete(request, request->key, request->key_len, exptime);
 			}
 			else {
-				pool->protocol->mutate(request, *key, request->key, request->key_len, invert ? -value : value, defval, defval_used, exptime);
+				pool->protocol->mutate(request, key, request->key, request->key_len, invert ? -value : value, defval, defval_used, exptime);
 			}
 
 			/* schedule request */
-			if (mmc_pool_schedule_key(pool, request->key, request->key_len, request, MEMCACHE_G(redundancy) TSRMLS_CC) != MMC_OK) {
+			if (mmc_pool_schedule_key(pool, request->key, request->key_len, request, MEMCACHE_G(redundancy)) != MMC_OK) {
 				continue;
 			}
 
 			/* begin sending requests immediatly */
-			mmc_pool_select(pool TSRMLS_CC);
-		}
+			mmc_pool_select(pool);
+		} ZEND_HASH_FOREACH_END();
+
 	}
 	else {
 		/* changed to true/false by mmc_numeric_response_handler or set to a value
@@ -672,14 +671,14 @@ static void php_mmc_numeric(INTERNAL_FUN
 
 		/* allocate request */
 		request = mmc_pool_request(pool, MMC_PROTO_TCP,
-			mmc_numeric_response_handler, return_value, mmc_pool_failover_handler, NULL TSRMLS_CC);
+			mmc_numeric_response_handler, return_value, mmc_pool_failover_handler, NULL);
 
 		request->value_handler = mmc_value_handler_single;
 		request->value_handler_param = value_handler_param;
 
 		if (mmc_prepare_key(keys, request->key, &(request->key_len)) != MMC_OK) {
 			mmc_pool_release(pool, request);
-			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid key");
+			php_error_docref(NULL, E_WARNING, "Invalid key");
 			RETURN_FALSE;
 		}
 
@@ -691,63 +690,53 @@ static void php_mmc_numeric(INTERNAL_FUN
 		}
 
 		/* schedule request */
-		if (mmc_pool_schedule_key(pool, request->key, request->key_len, request, MEMCACHE_G(redundancy) TSRMLS_CC) != MMC_OK) {
+		if (mmc_pool_schedule_key(pool, request->key, request->key_len, request, MEMCACHE_G(redundancy)) != MMC_OK) {
 			RETURN_FALSE;
 		}
 	}
 
 	/* execute all requests */
-	mmc_pool_run(pool TSRMLS_CC);
+	mmc_pool_run(pool);
 }
 /* }}} */
 
-mmc_t *mmc_find_persistent(const char *host, int host_len, unsigned short port, unsigned short udp_port, double timeout, int retry_interval TSRMLS_DC) /* {{{ */
+mmc_t *mmc_find_persistent(const char *host, int host_len, unsigned short port, unsigned short udp_port, double timeout, int retry_interval) /* {{{ */
 {
 	mmc_t *mmc;
-	zend_rsrc_list_entry *le;
+	zend_resource *le;
 	char *key;
 	int key_len;
 
 	key_len = spprintf(&key, 0, "memcache:server:%s:%u:%u", host, port, udp_port);
 
-	if (zend_hash_find(&EG(persistent_list), key, key_len+1, (void **)&le) == FAILURE) {
-		zend_rsrc_list_entry new_le;
+	if ((le = zend_hash_str_find_ptr(&EG(persistent_list), key, key_len)) == NULL) {
+		mmc = mmc_server_new(host, host_len, port, udp_port, 1, timeout, retry_interval);
 
-		mmc = mmc_server_new(host, host_len, port, udp_port, 1, timeout, retry_interval TSRMLS_CC);
-		new_le.type = le_memcache_server;
-		new_le.ptr  = mmc;
+		le = zend_register_resource(mmc, le_memcache_server);
 
 		/* register new persistent connection */
-		if (zend_hash_update(&EG(persistent_list), key, key_len+1, (void *)&new_le, sizeof(zend_rsrc_list_entry), NULL) == FAILURE) {
-			mmc_server_free(mmc TSRMLS_CC);
+		if (zend_hash_str_update_mem(&EG(persistent_list), key, key_len, le, sizeof(*le)) == NULL) {
+			mmc_server_free(mmc);
 			mmc = NULL;
 		} else {
-#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION == 3)
-			zend_list_insert(mmc, le_memcache_server);
-#else
-			zend_list_insert(mmc, le_memcache_server TSRMLS_CC);
-#endif
+			MEMCACHE_LIST_INSERT(mmc, le_memcache_server);
 		}
 	}
 	else if (le->type != le_memcache_server || le->ptr == NULL) {
-		zend_rsrc_list_entry new_le;
-		zend_hash_del(&EG(persistent_list), key, key_len+1);
+		zend_hash_str_del(&EG(persistent_list), key, key_len);
 
-		mmc = mmc_server_new(host, host_len, port, udp_port, 1, timeout, retry_interval TSRMLS_CC);
-		new_le.type = le_memcache_server;
-		new_le.ptr  = mmc;
+		mmc = mmc_server_new(host, host_len, port, udp_port, 1, timeout, retry_interval);
+		le->type = le_memcache_server;
+		le->ptr  = mmc;
+		GC_REFCOUNT(le) = 1;
 
 		/* register new persistent connection */
-		if (zend_hash_update(&EG(persistent_list), key, key_len+1, (void *)&new_le, sizeof(zend_rsrc_list_entry), NULL) == FAILURE) {
-			mmc_server_free(mmc TSRMLS_CC);
+		if (zend_hash_str_update_mem(&EG(persistent_list), key, key_len, le, sizeof(*le)) == NULL) {
+			mmc_server_free(mmc);
 			mmc = NULL;
 		}
 		else {
-#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION == 3)
-			zend_list_insert(mmc, le_memcache_server);
-#else
-			zend_list_insert(mmc, le_memcache_server TSRMLS_CC);
-#endif
+			MEMCACHE_LIST_INSERT(mmc, le_memcache_server);
 		}
 	}
 	else {
@@ -771,49 +760,54 @@ mmc_t *mmc_find_persistent(const char *h
 
 static mmc_t *php_mmc_pool_addserver(
 	zval *mmc_object, const char *host, int host_len, long tcp_port, long udp_port, long weight,
-	zend_bool persistent, double timeout, long retry_interval, zend_bool status, mmc_pool_t **pool_result TSRMLS_DC) /* {{{ */
+	zend_bool persistent, double timeout, long retry_interval, zend_bool status, mmc_pool_t **pool_result) /* {{{ */
 {
-	zval **connection;
+	zval *connection;
 	mmc_pool_t *pool;
 	mmc_t *mmc;
-	int list_id, resource_type;
+	zend_resource *list_res;
 
 	if (weight < 1) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "weight must be a positive integer");
+		php_error_docref(NULL, E_WARNING, "weight must be a positive integer");
 		return NULL;
 	}
 
+	if (tcp_port > 65635 || tcp_port < 0) {
+		php_error_docref(NULL, E_WARNING, "invalid tcp port number");
+		return NULL;
+	}
+	if (udp_port > 65635 || udp_port < 0) {
+		php_error_docref(NULL, E_WARNING, "invalid udp port number");
+		return NULL;
+	}
 	/* initialize pool if need be */
-	if (zend_hash_find(Z_OBJPROP_P(mmc_object), "connection", sizeof("connection"), (void **)&connection) == FAILURE) {
-		pool = mmc_pool_new(TSRMLS_C);
+	if ((connection = zend_hash_str_find(Z_OBJPROP_P(mmc_object), "connection", sizeof("connection")-1)) == NULL) {
+		pool = mmc_pool_new();
 		pool->failure_callback = &php_mmc_failure_callback;
-#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION == 3)
-		list_id = zend_list_insert(pool, le_memcache_pool);
-#else
-		list_id = zend_list_insert(pool, le_memcache_pool TSRMLS_CC);
-#endif
-		add_property_resource(mmc_object, "connection", list_id);
+		list_res = zend_register_resource(pool, le_memcache_pool);
+		add_property_resource(mmc_object, "connection", list_res);
+		GC_REFCOUNT(list_res)++;
 	}
 	else {
-		pool = (mmc_pool_t *)zend_list_find(Z_LVAL_PP(connection), &resource_type);
-		if (!pool || resource_type != le_memcache_pool) {
-			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unknown connection identifier");
+		pool = zend_fetch_resource_ex(connection, "connection", le_memcache_pool);
+		if (!pool) {
+			php_error_docref(NULL, E_WARNING, "Unknown connection identifier");
 			return NULL;
 		}
 	}
 
 	/* binary protocol isn't support over UDP yet */
 	if (udp_port && pool->protocol == &mmc_binary_protocol) {
-		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "binary protocol isn't support over UDP, defaulting to TCP");
+		php_error_docref(NULL, E_NOTICE, "binary protocol isn't support over UDP, defaulting to TCP");
 		udp_port = 0;
 	}
 
 	/* lazy initialization of server struct */
 	if (persistent && status) {
-		mmc = mmc_find_persistent(host, host_len, tcp_port, udp_port, timeout, retry_interval TSRMLS_CC);
+		mmc = mmc_find_persistent(host, host_len, (unsigned short) tcp_port, (unsigned short) udp_port, timeout, retry_interval);
 	}
 	else {
-		mmc = mmc_server_new(host, host_len, tcp_port, udp_port, 0, timeout, retry_interval TSRMLS_CC);
+		mmc = mmc_server_new(host, host_len, (unsigned short) tcp_port, (unsigned short) udp_port, 0, timeout, retry_interval);
 	}
 
 	/* add server in failed mode */
@@ -828,6 +822,27 @@ static mmc_t *php_mmc_pool_addserver(
 		*pool_result = pool;
 	}
 
+	if (pool->protocol == &mmc_binary_protocol) {
+		zval rv1, rv2;
+		zval *username = zend_read_property(memcache_ce, mmc_object, "username", strlen("username"), 1, &rv1);
+		zval *password = zend_read_property(memcache_ce, mmc_object, "password", strlen("password"), 1, &rv2);
+		if (Z_TYPE_P(username) == IS_STRING && Z_TYPE_P(password) == IS_STRING) {
+			if (Z_STRLEN_P(username) > 1  && Z_STRLEN_P(password) > 1) {
+				mmc_request_t *request;
+				zval sasl_value;
+
+				/* allocate request */
+				request = mmc_pool_request(pool, MMC_PROTO_TCP, mmc_stored_handler, &sasl_value, mmc_pool_failover_handler, NULL);
+				pool->protocol->set_sasl_auth_data(pool, request,  Z_STRVAL_P(username),  Z_STRVAL_P(password));
+
+				/* schedule request */
+				if (mmc_pool_schedule_key(pool, request->key, request->key_len, request, MEMCACHE_G(redundancy)) != MMC_OK) {
+					return NULL;
+				}
+			}
+		}
+	}
+
 	return mmc;
 }
 /* }}} */
@@ -837,51 +852,46 @@ static void php_mmc_connect(INTERNAL_FUN
 	zval *mmc_object = getThis();
 	mmc_pool_t *pool;
 	mmc_t *mmc;
-
 	char *host;
-	int host_len;
-	long tcp_port = MEMCACHE_G(default_port);
+	size_t host_len;
+	zend_long tcp_port = MEMCACHE_G(default_port);
 	double timeout = MMC_DEFAULT_TIMEOUT;
 
-	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ld", &host, &host_len, &tcp_port, &timeout) == FAILURE) {
+	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|ld", &host, &host_len, &tcp_port, &timeout) == FAILURE) {
 		return;
 	}
 
 	/* initialize pool and object if need be */
 	if (!mmc_object) {
-		int list_id;
-		mmc_pool_t *pool = mmc_pool_new(TSRMLS_C);
+		zend_resource *list_res;
+		mmc_pool_t *pool = mmc_pool_new();
 		pool->failure_callback = &php_mmc_failure_callback;
-#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION == 3)
-		list_id = zend_list_insert(pool, le_memcache_pool);
-#else
-		list_id = zend_list_insert(pool, le_memcache_pool TSRMLS_CC);
-#endif
+		list_res = zend_register_resource(pool, le_memcache_pool);
 		mmc_object = return_value;
 		object_init_ex(mmc_object, memcache_ce);
-		add_property_resource(mmc_object, "connection", list_id);
-	}
-	else {
+		add_property_resource(mmc_object, "connection", list_res);
+		GC_REFCOUNT(list_res)++;
+	} else {
 		RETVAL_TRUE;
 	}
 
-	mmc = php_mmc_pool_addserver(mmc_object, host, host_len, tcp_port, 0, 1, persistent, timeout, MMC_DEFAULT_RETRY, 1, NULL TSRMLS_CC);
+	mmc = php_mmc_pool_addserver(mmc_object, host, host_len, tcp_port, 0, 1, persistent, timeout, MMC_DEFAULT_RETRY, 1, NULL);
 	if (mmc == NULL) {
 		RETURN_FALSE;
 	}
 
 	/* force a reconnect attempt if stream EOF */
 	if (mmc->tcp.stream != NULL && php_stream_eof(mmc->tcp.stream)) {
-		mmc_server_disconnect(mmc, &(mmc->tcp) TSRMLS_CC);
+		mmc_server_disconnect(mmc, &(mmc->tcp));
 	}
 
-	if (!mmc_get_pool(mmc_object, &pool TSRMLS_CC)) {
+	if (!mmc_get_pool(mmc_object, &pool)) {
 		RETURN_FALSE;
 	}
 
 	/* force a tcp connect (if not persistently connected) */
-	if (mmc_pool_open(pool, mmc, &(mmc->tcp), 0 TSRMLS_CC) != MMC_OK) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Can't connect to %s:%d, %s (%d)", host, mmc->tcp.port, mmc->error ? mmc->error : "Unknown error", mmc->errnum);
+	if (mmc_pool_open(pool, mmc, &(mmc->tcp), 0) != MMC_OK) {
+		php_error_docref(NULL, E_WARNING, "Can't connect to %s:%d, %s (%d)", host, mmc->tcp.port, mmc->error ? mmc->error : "Unknown error", mmc->errnum);
 		RETURN_FALSE;
 	}
 }
@@ -890,10 +900,11 @@ static void php_mmc_connect(INTERNAL_FUN
 /*
  * STAT 6:chunk_size 64
  */
-static int mmc_stats_parse_stat(char *start, char *end, zval *result TSRMLS_DC)  /* {{{ */
+static int mmc_stats_parse_stat(char *start, char *end, zval *result)  /* {{{ */
 {
-	char *space, *colon, *key;
-	long index = 0;
+	char *key;
+	const char *space, *colon;
+	zend_long index = 0;
 
 	if (Z_TYPE_P(result) != IS_ARRAY) {
 		array_init(result);
@@ -906,28 +917,29 @@ static int mmc_stats_parse_stat(char *st
 
 	/* find colon delimiting subkeys */
 	if ((colon = php_memnstr(start, ":", 1, space - 1)) != NULL) {
-		zval *element, **elem;
+		zval *element, *elem;
+		zval new_element;
 		key = estrndup(start, colon - start);
 
 		/* find existing or create subkey array in result */
 		if ((is_numeric_string(key, colon - start, &index, NULL, 0) &&
-			zend_hash_index_find(Z_ARRVAL_P(result), index, (void **)&elem) != FAILURE) ||
-			zend_hash_find(Z_ARRVAL_P(result), key, colon - start + 1, (void **)&elem) != FAILURE) {
-			element = *elem;
+			(elem = zend_hash_index_find(Z_ARRVAL_P(result), index)) != NULL) ||
+			(elem = zend_hash_str_find(Z_ARRVAL_P(result), key, colon - start)) != NULL) {
+			element = elem;
 		}
 		else {
-			MAKE_STD_ZVAL(element);
-			array_init(element);
-			add_assoc_zval_ex(result, key, colon - start + 1, element);
+			array_init(&new_element);
+			add_assoc_zval_ex(result, key, colon - start, &new_element);
+			element = &new_element;
 		}
 
 		efree(key);
-		return mmc_stats_parse_stat(colon + 1, end, element TSRMLS_CC);
+		return mmc_stats_parse_stat(((char *) colon) + 1, end, element);
 	}
 
 	/* no more subkeys, add value under last subkey */
 	key = estrndup(start, space - start);
-	add_assoc_stringl_ex(result, key, space - start + 1, space + 1, end - space, 1);
+	add_assoc_stringl_ex(result, key, ((char *) space) - start, ((char *) space) + 1, end - ((char *) space));
 	efree(key);
 
 	return 1;
@@ -937,10 +949,11 @@ static int mmc_stats_parse_stat(char *st
 /*
  * ITEM test_key [3 b; 1157099416 s]
  */
-static int mmc_stats_parse_item(char *start, char *end, zval *result TSRMLS_DC)  /* {{{ */
+static int mmc_stats_parse_item(char *start, char *end, zval *result)  /* {{{ */
 {
-	char *space, *value, *value_end, *key;
-	zval *element;
+	char *key;
+	const char *space, *value, *value_end;
+	zval element;
 
 	if (Z_TYPE_P(result) != IS_ARRAY) {
 		array_init(result);
@@ -951,8 +964,7 @@ static int mmc_stats_parse_item(char *st
 		return 0;
 	}
 
-	MAKE_STD_ZVAL(element);
-	array_init(element);
+	array_init(&element);
 
 	/* parse each contained value */
 	for (value = php_memnstr(space, "[", 1, end); value != NULL && value <= end; value = php_memnstr(value + 1, ";", 1, end)) {
@@ -961,22 +973,23 @@ static int mmc_stats_parse_item(char *st
 		} while (*value == ' ' && value <= end);
 
 		if (value <= end && (value_end = php_memnstr(value, " ", 1, end)) != NULL && value_end <= end) {
-			add_next_index_stringl(element, value, value_end - value, 1);
+			add_next_index_stringl(&element, value, value_end - value);
 		}
 	}
 
 	/* add parsed values under key */
 	key = estrndup(start, space - start);
-	add_assoc_zval_ex(result, key, space - start + 1, element);
+	add_assoc_zval_ex(result, key, space - start, &element);
 	efree(key);
 
 	return 1;
 }
 /* }}} */
 
-static int mmc_stats_parse_generic(char *start, char *end, zval *result TSRMLS_DC)  /* {{{ */
+static int mmc_stats_parse_generic(char *start, char *end, zval *result)  /* {{{ */
 {
-	char *space, *key;
+	const char *space;
+	char *key;
 
 	if (Z_TYPE_P(result) != IS_ARRAY) {
 		array_init(result);
@@ -985,11 +998,11 @@ static int mmc_stats_parse_generic(char
 	if (start < end) {
 		if ((space = php_memnstr(start, " ", 1, end)) != NULL) {
 			key = estrndup(start, space - start);
-			add_assoc_stringl_ex(result, key, space - start + 1, space + 1, end - space, 1);
+			add_assoc_stringl_ex(result, key, ((char *) space) - start + 1, ((char *) space) + 1, end - ((char *) space));
 			efree(key);
 		}
 		else {
-			add_next_index_stringl(result, start, end - start, 1);
+			add_next_index_stringl(result, start, end - start);
 		}
 	}
 	else {
@@ -1000,84 +1013,81 @@ static int mmc_stats_parse_generic(char
 }
 /* }}} */
 
-static void php_mmc_failure_callback(mmc_pool_t *pool, mmc_t *mmc, void *param TSRMLS_DC) /* {{{ */
+static void php_mmc_failure_callback(mmc_pool_t *pool, mmc_t *mmc, zval *param) /* {{{ */
 {
-	zval **callback;
+	zval *callback;
 
 	/* check for userspace callback */
-	if (param != NULL && zend_hash_find(Z_OBJPROP_P((zval *)param), "_failureCallback", sizeof("_failureCallback"), (void **)&callback) == SUCCESS && Z_TYPE_PP(callback) != IS_NULL) {
-		if (IS_CALLABLE(*callback, 0, NULL)) {
-			zval *retval = NULL;
+	if (!Z_ISUNDEF_P(param) && (callback = zend_hash_str_find(Z_OBJPROP_P((zval *)param), "_failureCallback", sizeof("_failureCallback")-1)) != NULL && Z_TYPE_P(callback) != IS_NULL) {
+		if (MEMCACHE_IS_CALLABLE(callback, 0, NULL)) {
+			zval retval;
 			zval *host, *tcp_port, *udp_port, *error, *errnum;
-			zval **params[5];
+			zval params[5];
 
-			params[0] = &host;
-			params[1] = &tcp_port;
-			params[2] = &udp_port;
-			params[3] = &error;
-			params[4] = &errnum;
-
-			MAKE_STD_ZVAL(host);
-			MAKE_STD_ZVAL(tcp_port); MAKE_STD_ZVAL(udp_port);
-			MAKE_STD_ZVAL(error); MAKE_STD_ZVAL(errnum);
+			ZVAL_UNDEF(&retval);
 
-			ZVAL_STRING(host, mmc->host, 1);
+			host = &params[0];
+			tcp_port = &params[1];
+			udp_port = &params[2];
+			error = &params[3];
+			errnum = &params[4];
+
+			ZVAL_STRING(host, mmc->host);
 			ZVAL_LONG(tcp_port, mmc->tcp.port); ZVAL_LONG(udp_port, mmc->udp.port);
 
 			if (mmc->error != NULL) {
-				ZVAL_STRING(error, mmc->error, 1);
+				ZVAL_STRING(error, mmc->error);
 			}
 			else {
 				ZVAL_NULL(error);
 			}
 			ZVAL_LONG(errnum, mmc->errnum);
 
-			call_user_function_ex(EG(function_table), NULL, *callback, &retval, 5, params, 0, NULL TSRMLS_CC);
+			call_user_function_ex(EG(function_table), NULL, callback, &retval, 5, params, 0, NULL);
 
-			zval_ptr_dtor(&host);
-			zval_ptr_dtor(&tcp_port); zval_ptr_dtor(&udp_port);
-			zval_ptr_dtor(&error); zval_ptr_dtor(&errnum);
+			zval_ptr_dtor(host);
+			zval_ptr_dtor(tcp_port); zval_ptr_dtor(udp_port);
+			zval_ptr_dtor(error); zval_ptr_dtor(errnum);
 
-			if (retval != NULL) {
+			if (Z_TYPE(retval) != IS_UNDEF) {
 				zval_ptr_dtor(&retval);
 			}
 		}
 		else {
-			php_mmc_set_failure_callback(pool, (zval *)param, NULL TSRMLS_CC);
-			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid failure callback");
+			php_mmc_set_failure_callback(pool, (zval *)param, NULL);
+			php_error_docref(NULL, E_WARNING, "Invalid failure callback");
 		}
 	}
 	else {
-		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Server %s (tcp %d, udp %d) failed with: %s (%d)",
+		php_error_docref(NULL, E_NOTICE, "Server %s (tcp %d, udp %d) failed with: %s (%d)",
 			mmc->host, mmc->tcp.port, mmc->udp.port, mmc->error, mmc->errnum);
 	}
 }
 /* }}} */
 
-static void php_mmc_set_failure_callback(mmc_pool_t *pool, zval *mmc_object, zval *callback TSRMLS_DC)  /* {{{ */
+static void php_mmc_set_failure_callback(mmc_pool_t *pool, zval *mmc_object, zval *callback)  /* {{{ */
 {
 	// Decrease refcount of old mmc_object
-	if (pool->failure_callback_param) {
-		zval_ptr_dtor((zval **)&pool->failure_callback_param);
+	if (!Z_ISUNDEF(pool->failure_callback_param)) {
+		Z_DELREF(pool->failure_callback_param);
 	}
 
 	if (callback != NULL) {
-		zval *callback_tmp;
-		ALLOC_ZVAL(callback_tmp);
+		zval callback_tmp;
+
+		callback_tmp = *callback;
+		zval_copy_ctor(&callback_tmp);
+
+		add_property_zval(mmc_object, "_failureCallback", &callback_tmp);
 
-		*callback_tmp = *callback;
-		zval_copy_ctor(callback_tmp);
-		INIT_PZVAL(callback_tmp);
-
-		add_property_zval(mmc_object, "_failureCallback", callback_tmp);
-		pool->failure_callback_param = mmc_object;
-		zval_add_ref(&mmc_object);
+		zval_ptr_dtor(&callback_tmp);
 
-		INIT_PZVAL(callback_tmp);
+		pool->failure_callback_param = *mmc_object;
+		Z_ADDREF_P(mmc_object);
 	}
 	else {
 		add_property_null(mmc_object, "_failureCallback");
-		pool->failure_callback_param = NULL;
+		ZVAL_UNDEF(&pool->failure_callback_param);
 	}
 }
 /* }}} */
@@ -1095,33 +1105,33 @@ PHP_NAMED_FUNCTION(zif_memcache_pool_con
 	mmc_t *mmc;
 
 	char *host;
-	int host_len;
-	long tcp_port = MEMCACHE_G(default_port), udp_port = 0, weight = 1, retry_interval = MMC_DEFAULT_RETRY;
+	size_t host_len;
+	zend_long tcp_port = MEMCACHE_G(default_port), udp_port = 0, weight = 1, retry_interval = MMC_DEFAULT_RETRY;
 	double timeout = MMC_DEFAULT_TIMEOUT;
 	zend_bool persistent = 1;
 
-	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|llbldl",
+	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|llbldl",
 		&host, &host_len, &tcp_port, &udp_port, &persistent, &weight, &timeout, &retry_interval) == FAILURE) {
 		return;
 	}
 
-	mmc = php_mmc_pool_addserver(mmc_object, host, host_len, tcp_port, udp_port, weight, persistent, timeout, retry_interval, 1, NULL TSRMLS_CC);
+	mmc = php_mmc_pool_addserver(mmc_object, host, host_len, tcp_port, udp_port, weight, persistent, timeout, retry_interval, 1, NULL);
 	if (mmc == NULL) {
 		RETURN_FALSE;
 	}
 
 	/* force a reconnect attempt if stream EOF */
 	if (mmc->tcp.stream != NULL && php_stream_eof(mmc->tcp.stream)) {
-		mmc_server_disconnect(mmc, &(mmc->tcp) TSRMLS_CC);
+		mmc_server_disconnect(mmc, &(mmc->tcp));
 	}
 
-	if (!mmc_get_pool(mmc_object, &pool TSRMLS_CC)) {
+	if (!mmc_get_pool(mmc_object, &pool)) {
 		RETURN_FALSE;
 	}
 
 	/* force a tcp connect (if not persistently connected) */
-	if (mmc_pool_open(pool, mmc, &(mmc->tcp), 0 TSRMLS_CC) != MMC_OK) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Can't connect to %s:%d, %s (%d)", host, mmc->tcp.port, mmc->error ? mmc->error : "Unknown error", mmc->errnum);
+	if (mmc_pool_open(pool, mmc, &(mmc->tcp), 0) != MMC_OK) {
+		php_error_docref(NULL, E_WARNING, "Can't connect to %s:%d, %s (%d)", host, mmc->tcp.port, mmc->error ? mmc->error : "Unknown error", mmc->errnum);
 		RETURN_FALSE;
 	}
 
@@ -1153,17 +1163,17 @@ PHP_NAMED_FUNCTION(zif_memcache_pool_add
 	mmc_t *mmc;
 
 	char *host;
-	int host_len;
-	long tcp_port = MEMCACHE_G(default_port), udp_port = 0, weight = 1, retry_interval = MMC_DEFAULT_RETRY;
+	size_t host_len;
+	zend_long tcp_port = MEMCACHE_G(default_port), udp_port = 0, weight = 1, retry_interval = MMC_DEFAULT_RETRY;
 	double timeout = MMC_DEFAULT_TIMEOUT;
 	zend_bool persistent = 1, status = 1;
 
-	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|llbldlb",
+	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|llbldlb",
 		&host, &host_len, &tcp_port, &udp_port, &persistent, &weight, &timeout, &retry_interval, &status) == FAILURE) {
 		return;
 	}
 
-	mmc = php_mmc_pool_addserver(mmc_object, host, host_len, tcp_port, udp_port, weight, persistent, timeout, retry_interval, status, NULL TSRMLS_CC);
+	mmc = php_mmc_pool_addserver(mmc_object, host, host_len, tcp_port, udp_port, weight, persistent, timeout, retry_interval, status, NULL);
 	if (mmc == NULL) {
 		RETURN_FALSE;
 	}
@@ -1180,28 +1190,28 @@ PHP_NAMED_FUNCTION(zif_memcache_pool_fin
 	zval *mmc_object = getThis();
 	mmc_pool_t *pool;
 	mmc_t *mmc;
-	
+
 	zval *zkey;
 	char key[MMC_MAX_KEY_LEN + 1];
 	unsigned int key_len;
-	char *hostname;
+	zend_string *hostname;
 
-	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &zkey) == FAILURE) {
+	if (zend_parse_parameters(ZEND_NUM_ARGS(), "z", &zkey) == FAILURE) {
 		return;
 	}
-	
-	if (!mmc_get_pool(mmc_object, &pool TSRMLS_CC) || !pool->num_servers) {
+
+	if (!mmc_get_pool(mmc_object, &pool) || !pool->num_servers) {
 		RETURN_FALSE;
 	}
 
 	if (mmc_prepare_key(zkey, key, &key_len) != MMC_OK) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid key");
+		php_error_docref(NULL, E_WARNING, "Invalid key");
 		RETURN_FALSE;
 	}
-	
-	mmc = mmc_pool_find(pool, key, key_len TSRMLS_CC);
-	spprintf(&hostname, 0, "%s:%d", mmc->host, mmc->tcp.port);	
-	RETURN_STRING(hostname, 0);
+
+	mmc = mmc_pool_find(pool, key, key_len);
+	hostname = strpprintf(0, "%s:%d", mmc->host, mmc->tcp.port);
+	RETURN_STR(hostname);
 }
 /* }}} */
 
@@ -1214,38 +1224,38 @@ PHP_FUNCTION(memcache_add_server)
 	mmc_t *mmc;
 
 	char *host;
-	int host_len;
-	long tcp_port = MEMCACHE_G(default_port), weight = 1, retry_interval = MMC_DEFAULT_RETRY;
+	size_t host_len;
+	zend_long tcp_port = MEMCACHE_G(default_port), weight = 1, retry_interval = MMC_DEFAULT_RETRY;
 	double timeout = MMC_DEFAULT_TIMEOUT;
 	zend_bool persistent = 1, status = 1;
 
 	if (mmc_object) {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|lbldlbz",
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|lbldlbz",
 			&host, &host_len, &tcp_port, &persistent, &weight, &timeout, &retry_interval, &status, &failure_callback) == FAILURE) {
 			return;
 		}
 	}
 	else {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Os|lbldlbz", &mmc_object, memcache_ce,
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "Os|lbldlbz", &mmc_object, memcache_ce,
 			&host, &host_len, &tcp_port, &persistent, &weight, &timeout, &retry_interval, &status, &failure_callback) == FAILURE) {
 			return;
 		}
 	}
 
 	if (failure_callback != NULL && Z_TYPE_P(failure_callback) != IS_NULL) {
-		if (!IS_CALLABLE(failure_callback, 0, NULL)) {
-			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid failure callback");
+		if (!MEMCACHE_IS_CALLABLE(failure_callback, 0, NULL)) {
+			php_error_docref(NULL, E_WARNING, "Invalid failure callback");
 			RETURN_FALSE;
 		}
 	}
 
-	mmc = php_mmc_pool_addserver(mmc_object, host, host_len, tcp_port, 0, weight, persistent, timeout, retry_interval, status, &pool TSRMLS_CC);
+	mmc = php_mmc_pool_addserver(mmc_object, host, host_len, tcp_port, 0, weight, persistent, timeout, retry_interval, status, &pool);
 	if (mmc == NULL) {
 		RETURN_FALSE;
 	}
 
 	if (failure_callback != NULL && Z_TYPE_P(failure_callback) != IS_NULL) {
-		php_mmc_set_failure_callback(pool, mmc_object, failure_callback TSRMLS_CC);
+		php_mmc_set_failure_callback(pool, mmc_object, failure_callback);
 	}
 
 	RETURN_TRUE;
@@ -1259,26 +1269,27 @@ PHP_FUNCTION(memcache_set_server_params)
 	zval *mmc_object = getThis(), *failure_callback = NULL;
 	mmc_pool_t *pool;
 	mmc_t *mmc = NULL;
-	long tcp_port = MEMCACHE_G(default_port), retry_interval = MMC_DEFAULT_RETRY;
+	zend_long tcp_port = MEMCACHE_G(default_port), retry_interval = MMC_DEFAULT_RETRY;
 	double timeout = MMC_DEFAULT_TIMEOUT;
 	zend_bool status = 1;
-	int host_len, i;
+	size_t host_len;
+	int i;
 	char *host;
 
 	if (mmc_object) {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ldlbz",
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|ldlbz",
 			&host, &host_len, &tcp_port, &timeout, &retry_interval, &status, &failure_callback) == FAILURE) {
 			return;
 		}
 	}
 	else {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Os|ldlbz", &mmc_object, memcache_pool_ce,
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "Os|ldlbz", &mmc_object, memcache_pool_ce,
 			&host, &host_len, &tcp_port, &timeout, &retry_interval, &status, &failure_callback) == FAILURE) {
 			return;
 		}
 	}
 
-	if (!mmc_get_pool(mmc_object, &pool TSRMLS_CC)) {
+	if (!mmc_get_pool(mmc_object, &pool)) {
 		RETURN_FALSE;
 	}
 
@@ -1290,13 +1301,13 @@ PHP_FUNCTION(memcache_set_server_params)
 	}
 
 	if (!mmc) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Server not found in pool");
+		php_error_docref(NULL, E_WARNING, "Server not found in pool");
 		RETURN_FALSE;
 	}
 
 	if (failure_callback != NULL && Z_TYPE_P(failure_callback) != IS_NULL) {
-		if (!IS_CALLABLE(failure_callback, 0, NULL)) {
-			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid failure callback");
+		if (!MEMCACHE_IS_CALLABLE(failure_callback, 0, NULL)) {
+			php_error_docref(NULL, E_WARNING, "Invalid failure callback");
 			RETURN_FALSE;
 		}
 	}
@@ -1324,10 +1335,10 @@ PHP_FUNCTION(memcache_set_server_params)
 
 	if (failure_callback != NULL) {
 		if (Z_TYPE_P(failure_callback) != IS_NULL) {
-			php_mmc_set_failure_callback(pool, mmc_object, failure_callback TSRMLS_CC);
+			php_mmc_set_failure_callback(pool, mmc_object, failure_callback);
 		}
 		else {
-			php_mmc_set_failure_callback(pool, mmc_object, NULL TSRMLS_CC);
+			php_mmc_set_failure_callback(pool, mmc_object, NULL);
 		}
 	}
 
@@ -1343,34 +1354,34 @@ PHP_FUNCTION(memcache_set_failure_callba
 	mmc_pool_t *pool;
 
 	if (mmc_object) {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z",
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "z",
 			&failure_callback) == FAILURE) {
 			return;
 		}
 	}
 	else {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Oz", &mmc_object, memcache_pool_ce,
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "Oz", &mmc_object, memcache_pool_ce,
 			&failure_callback) == FAILURE) {
 			return;
 		}
 	}
 
-	if (!mmc_get_pool(mmc_object, &pool TSRMLS_CC)) {
+	if (!mmc_get_pool(mmc_object, &pool)) {
 		RETURN_FALSE;
 	}
 
 	if (Z_TYPE_P(failure_callback) != IS_NULL) {
-		if (!IS_CALLABLE(failure_callback, 0, NULL)) {
-			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid failure callback");
+		if (!MEMCACHE_IS_CALLABLE(failure_callback, 0, NULL)) {
+			php_error_docref(NULL, E_WARNING, "Invalid failure callback");
 			RETURN_FALSE;
 		}
 	}
 
 	if (Z_TYPE_P(failure_callback) != IS_NULL) {
-		php_mmc_set_failure_callback(pool, mmc_object, failure_callback TSRMLS_CC);
+		php_mmc_set_failure_callback(pool, mmc_object, failure_callback);
 	}
 	else {
-		php_mmc_set_failure_callback(pool, mmc_object, NULL TSRMLS_CC);
+		php_mmc_set_failure_callback(pool, mmc_object, NULL);
 	}
 
 	RETURN_TRUE;
@@ -1384,22 +1395,23 @@ PHP_FUNCTION(memcache_get_server_status)
 	zval *mmc_object = getThis();
 	mmc_pool_t *pool;
 	mmc_t *mmc = NULL;
-	long tcp_port = MEMCACHE_G(default_port);
-	int host_len, i;
+	zend_long tcp_port = MEMCACHE_G(default_port);
+	size_t host_len;
+	int i;
 	char *host;
 
 	if (mmc_object) {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &host, &host_len, &tcp_port) == FAILURE) {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|l", &host, &host_len, &tcp_port) == FAILURE) {
 			return;
 		}
 	}
 	else {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Os|l", &mmc_object, memcache_pool_ce, &host, &host_len, &tcp_port) == FAILURE) {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "Os|l", &mmc_object, memcache_pool_ce, &host, &host_len, &tcp_port) == FAILURE) {
 			return;
 		}
 	}
 
-	if (!mmc_get_pool(mmc_object, &pool TSRMLS_CC)) {
+	if (!mmc_get_pool(mmc_object, &pool)) {
 		RETURN_FALSE;
 	}
 
@@ -1411,7 +1423,7 @@ PHP_FUNCTION(memcache_get_server_status)
 	}
 
 	if (!mmc) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Server not found in pool");
+		php_error_docref(NULL, E_WARNING, "Server not found in pool");
 		RETURN_FALSE;
 	}
 
@@ -1419,24 +1431,25 @@ PHP_FUNCTION(memcache_get_server_status)
 }
 /* }}} */
 
-static int mmc_version_handler(mmc_t *mmc, mmc_request_t *request, int response, const char *message, unsigned int message_len, void *param TSRMLS_DC) /*
+static int mmc_version_handler(mmc_t *mmc, mmc_request_t *request, int response, const char *message, unsigned int message_len, void *param) /*
 	parses the VERSION response line, param is a zval pointer to store version into {{{ */
 {
 	if (response != MMC_RESPONSE_ERROR) {
 		char *version = emalloc(message_len + 1);
 
 		if (sscanf(message, "VERSION %s", version) == 1) {
-			ZVAL_STRING((zval *)param, version, 0);
+			ZVAL_STRING((zval *)param, version);
+			efree(version);
 		}
 		else {
 			efree(version);
-			ZVAL_STRINGL((zval *)param, (char *)message, message_len, 1);
+			ZVAL_STRINGL((zval *)param, (char *)message, message_len);
 		}
 
 		return MMC_REQUEST_DONE;
 	}
 
-	return mmc_request_failure(mmc, request->io, message, message_len, 0 TSRMLS_CC);
+	return mmc_request_failure(mmc, request->io, message, message_len, 0);
 }
 /* }}} */
 
@@ -1450,23 +1463,23 @@ PHP_FUNCTION(memcache_get_version)
 	mmc_request_t *request;
 
 	if (mmc_object == NULL) {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &mmc_object, memcache_pool_ce) == FAILURE) {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "O", &mmc_object, memcache_pool_ce) == FAILURE) {
 			return;
 		}
 	}
 
-	if (!mmc_get_pool(mmc_object, &pool TSRMLS_CC) || !pool->num_servers) {
+	if (!mmc_get_pool(mmc_object, &pool) || !pool->num_servers) {
 		RETURN_FALSE;
 	}
 
 	RETVAL_FALSE;
 	for (i=0; i<pool->num_servers; i++) {
 		/* run command and check for valid return value */
-		request = mmc_pool_request(pool, MMC_PROTO_TCP, mmc_version_handler, return_value, NULL, NULL TSRMLS_CC);
+		request = mmc_pool_request(pool, MMC_PROTO_TCP, mmc_version_handler, return_value, NULL, NULL);
 		pool->protocol->version(request);
 
-		if (mmc_pool_schedule(pool, pool->servers[i], request TSRMLS_CC) == MMC_OK) {
-			mmc_pool_run(pool TSRMLS_CC);
+		if (mmc_pool_schedule(pool, pool->servers[i], request) == MMC_OK) {
+			mmc_pool_run(pool);
 
 			if (Z_TYPE_P(return_value) == IS_STRING) {
 				break;
@@ -1526,7 +1539,7 @@ PHP_FUNCTION(memcache_prepend)
 
 int mmc_value_handler_multi(
 	const char *key, unsigned int key_len, zval *value,
-	unsigned int flags, unsigned long cas, void *param TSRMLS_DC) /*
+	unsigned int flags, unsigned long cas, void *param) /*
 	receives a multiple values, param is a zval** array to store value and flags in {{{ */
 {
 	zval **result = (zval **)param;
@@ -1535,14 +1548,14 @@ int mmc_value_handler_multi(
 	if (Z_TYPE_P(result[0]) != IS_ARRAY) {
 		array_init(result[0]);
 	}
-	add_assoc_zval_ex(result[0], (char *)key, key_len + 1, value);
+	add_assoc_zval_ex(result[0], (char *)key, key_len, value);
 
 	/* add flags to result */
 	if (result[1] != NULL) {
 		if (Z_TYPE_P(result[1]) != IS_ARRAY) {
 			array_init(result[1]);
 		}
-		add_assoc_long_ex(result[1], (char *)key, key_len + 1, flags);
+		add_assoc_long_ex(result[1], (char *)key, key_len, flags);
 	}
 
 	/* add CAS value to result */
@@ -1550,7 +1563,7 @@ int mmc_value_handler_multi(
 		if (Z_TYPE_P(result[2]) != IS_ARRAY) {
 			array_init(result[2]);
 		}
-		add_assoc_long_ex(result[2], (char *)key, key_len + 1, cas);
+		add_assoc_long_ex(result[2], (char *)key, key_len, cas);
 	}
 
 	return MMC_REQUEST_DONE;
@@ -1559,7 +1572,7 @@ int mmc_value_handler_multi(
 
 int mmc_value_handler_single(
 	const char *key, unsigned int key_len, zval *value,
-	unsigned int flags, unsigned long cas, void *param TSRMLS_DC) /*
+	unsigned int flags, unsigned long cas, void *param) /*
 	receives a single value, param is a zval pointer to store value to {{{ */
 {
 	zval **result = (zval **)param;
@@ -1577,32 +1590,27 @@ int mmc_value_handler_single(
 }
 /* }}} */
 
-static int mmc_value_failover_handler(mmc_pool_t *pool, mmc_t *mmc, mmc_request_t *request, void *param TSRMLS_DC) /*
+static int mmc_value_failover_handler(mmc_pool_t *pool, mmc_t *mmc, mmc_request_t *request, void *param) /*
 	uses keys and return value to reschedule requests to other servers, param is a zval ** pointer {{{ */
 {
-	zval **key, *keys = ((zval **)param)[0], **value_handler_param = (zval **)((void **)param)[1];
-	HashPosition pos;
+	zval *keys = ((zval **)param)[0], **value_handler_param = (zval **)((void **)param)[1];
+	zval *key;
 
 	if (!MEMCACHE_G(allow_failover) || request->failed_servers.len >= MEMCACHE_G(max_failover_attempts)) {
 		mmc_pool_release(pool, request);
 		return MMC_REQUEST_FAILURE;
 	}
 
-	zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(keys), &pos);
-
-	while (zend_hash_get_current_data_ex(Z_ARRVAL_P(keys), (void **)&key, &pos) == SUCCESS) {
-		zend_hash_move_forward_ex(Z_ARRVAL_P(keys), &pos);
-
-		/* re-schedule key if it does not exist in return value array */
+	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(keys), key) {
 		if (Z_TYPE_P(value_handler_param[0]) != IS_ARRAY ||
-			!zend_hash_exists(Z_ARRVAL_P(value_handler_param[0]), Z_STRVAL_PP(key), Z_STRLEN_PP(key) + 1))
-		{
-			mmc_pool_schedule_get(pool, MMC_PROTO_UDP,
-				value_handler_param[2] != NULL ? MMC_OP_GETS : MMC_OP_GET, *key,
-				request->value_handler, request->value_handler_param,
-				request->failover_handler, request->failover_handler_param, request TSRMLS_CC);
-		}
-	}
+					!zend_hash_str_exists(Z_ARRVAL_P(value_handler_param[0]), Z_STRVAL_P(key), Z_STRLEN_P(key)))
+				{
+					mmc_pool_schedule_get(pool, MMC_PROTO_UDP,
+						value_handler_param[2] != NULL ? MMC_OP_GETS : MMC_OP_GET, key,
+						request->value_handler, request->value_handler_param,
+						request->failover_handler, request->failover_handler_param, request);
+				}
+	} ZEND_HASH_FOREACH_END();
 
 	mmc_pool_release(pool, request);
 	return MMC_OK;
@@ -1618,17 +1626,17 @@ PHP_FUNCTION(memcache_get)
 	void *value_handler_param[3], *failover_handler_param[2];
 
 	if (mmc_object == NULL) {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Oz|zz", &mmc_object, memcache_pool_ce, &keys, &flags, &cas) == FAILURE) {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "Oz|z/z/", &mmc_object, memcache_pool_ce, &keys, &flags, &cas) == FAILURE) {
 			return;
 		}
 	}
 	else {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|zz", &keys, &flags, &cas) == FAILURE) {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "z|z/z/", &keys, &flags, &cas) == FAILURE) {
 			return;
 		}
 	}
 
-	if (!mmc_get_pool(mmc_object, &pool TSRMLS_CC) || !pool->num_servers) {
+	if (!mmc_get_pool(mmc_object, &pool) || !pool->num_servers) {
 		RETURN_FALSE;
 	}
 
@@ -1637,25 +1645,20 @@ PHP_FUNCTION(memcache_get)
 	value_handler_param[2] = cas;
 
 	if (Z_TYPE_P(keys) == IS_ARRAY) {
-		zval **key;
-		HashPosition pos;
-
+		zval *zv;
 		/* return empty array if no keys found */
 		array_init(return_value);
 
 		failover_handler_param[0] = keys;
 		failover_handler_param[1] = value_handler_param;
 
-		zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(keys), &pos);
-		while (zend_hash_get_current_data_ex(Z_ARRVAL_P(keys), (void **)&key, &pos) == SUCCESS) {
-			zend_hash_move_forward_ex(Z_ARRVAL_P(keys), &pos);
-
+		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(keys), zv) {
 			/* schedule request */
 			mmc_pool_schedule_get(pool, MMC_PROTO_UDP,
-				cas != NULL ? MMC_OP_GETS : MMC_OP_GET, *key,
+				cas != NULL ? MMC_OP_GETS : MMC_OP_GET, zv,
 				mmc_value_handler_multi, value_handler_param,
-				mmc_value_failover_handler, failover_handler_param, NULL TSRMLS_CC);
-		}
+				mmc_value_failover_handler, failover_handler_param, NULL);
+		} ZEND_HASH_FOREACH_END();
 	}
 	else {
 		mmc_request_t *request;
@@ -1665,30 +1668,30 @@ PHP_FUNCTION(memcache_get)
 
 		/* allocate request */
 		request = mmc_pool_request_get(
-			pool, MMC_PROTO_UDP,
+			pool, MMC_PROTO_TCP,
 			mmc_value_handler_single, value_handler_param,
-			mmc_pool_failover_handler, NULL TSRMLS_CC);
+			mmc_pool_failover_handler, NULL);
 
 		if (mmc_prepare_key(keys, request->key, &(request->key_len)) != MMC_OK) {
 			mmc_pool_release(pool, request);
-			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid key");
+			php_error_docref(NULL, E_WARNING, "Invalid key");
 			return;
 		}
 
 		pool->protocol->get(request, cas != NULL ? MMC_OP_GETS : MMC_OP_GET, keys, request->key, request->key_len);
 
 		/* schedule request */
-		if (mmc_pool_schedule_key(pool, request->key, request->key_len, request, 1 TSRMLS_CC) != MMC_OK) {
+		if (mmc_pool_schedule_key(pool, request->key, request->key_len, request, 1) != MMC_OK) {
 			return;
 		}
 	}
 
 	/* execute all requests */
-	mmc_pool_run(pool TSRMLS_CC);
+	mmc_pool_run(pool);
 }
 /* }}} */
 
-static int mmc_stats_handler(mmc_t *mmc, mmc_request_t *request, int response, const char *message, unsigned int message_len, void *param TSRMLS_DC) /*
+static int mmc_stats_handler(mmc_t *mmc, mmc_request_t *request, int response, const char *message, unsigned int message_len, void *param) /*
 	parses the stats response line, param is a zval pointer to store stats into {{{ */
 {
 	if (response != MMC_RESPONSE_ERROR)
@@ -1704,19 +1707,19 @@ static int mmc_stats_handler(mmc_t *mmc,
 			return MMC_REQUEST_DONE;
 		}
 		else if (mmc_str_left(line, "STAT ", message_len, sizeof("STAT ")-1)) {
-			if (mmc_stats_parse_stat(line + sizeof("STAT ")-1, line + message_len - 1, (zval *)param TSRMLS_CC)) {
+			if (mmc_stats_parse_stat(line + sizeof("STAT ")-1, line + message_len - 1, (zval *)param)) {
 				return MMC_REQUEST_AGAIN;
 			}
 		}
 		else if (mmc_str_left(line, "ITEM ", message_len, sizeof("ITEM ")-1)) {
-			if (mmc_stats_parse_item(line + sizeof("ITEM ")-1, line + message_len - 1, (zval *)param TSRMLS_CC)) {
+			if (mmc_stats_parse_item(line + sizeof("ITEM ")-1, line + message_len - 1, (zval *)param)) {
 				return MMC_REQUEST_AGAIN;
 			}
 		}
 		else if (mmc_str_left(line, "END", message_len, sizeof("END")-1)) {
 			return MMC_REQUEST_DONE;
 		}
-		else if (mmc_stats_parse_generic(line, line + message_len, (zval *)param TSRMLS_CC)) {
+		else if (mmc_stats_parse_generic(line, line + message_len, (zval *)param)) {
 			return MMC_REQUEST_AGAIN;
 		}
 
@@ -1725,7 +1728,7 @@ static int mmc_stats_handler(mmc_t *mmc,
 		return MMC_REQUEST_FAILURE;
 	}
 
-	return mmc_request_failure(mmc, request->io, message, message_len, 0 TSRMLS_CC);
+	return mmc_request_failure(mmc, request->io, message, message_len, 0);
 }
 /* }}} */
 
@@ -1748,48 +1751,49 @@ PHP_FUNCTION(memcache_get_stats)
 	zval *mmc_object = getThis();
 
 	char *type = NULL;
-	int i, type_len = 0;
-	long slabid = 0, limit = MMC_DEFAULT_CACHEDUMP_LIMIT;
+	int i;
+	size_t type_len = 0;
+	zend_long slabid = 0, limit = MMC_DEFAULT_CACHEDUMP_LIMIT;
 	mmc_request_t *request;
 
 	if (mmc_object == NULL) {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O|sll", &mmc_object, memcache_pool_ce, &type, &type_len, &slabid, &limit) == FAILURE) {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "O|sll", &mmc_object, memcache_pool_ce, &type, &type_len, &slabid, &limit) == FAILURE) {
 			return;
 		}
 	}
 	else {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|sll", &type, &type_len, &slabid, &limit) == FAILURE) {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "|sll", &type, &type_len, &slabid, &limit) == FAILURE) {
 			return;
 		}
 	}
 
-	if (!mmc_get_pool(mmc_object, &pool TSRMLS_CC) || !pool->num_servers) {
+	if (!mmc_get_pool(mmc_object, &pool) || !pool->num_servers) {
 		RETURN_FALSE;
 	}
 
 	if (!mmc_stats_checktype(type)) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid stats type");
+		php_error_docref(NULL, E_WARNING, "Invalid stats type");
 		RETURN_FALSE;
 	}
 
 	ZVAL_FALSE(return_value);
 
 	for (i=0; i<pool->num_servers; i++) {
-		request = mmc_pool_request(pool, MMC_PROTO_TCP, mmc_stats_handler, return_value, NULL, NULL TSRMLS_CC);
+		request = mmc_pool_request(pool, MMC_PROTO_TCP, mmc_stats_handler, return_value, NULL, NULL);
 		pool->protocol->stats(request, type, slabid, limit);
 
 		/* run command and check for valid return value */
-		if (mmc_pool_schedule(pool, pool->servers[i], request TSRMLS_CC) == MMC_OK) {
-			mmc_pool_run(pool TSRMLS_CC);
+		if (mmc_pool_schedule(pool, pool->servers[i], request) == MMC_OK) {
+			mmc_pool_run(pool);
 
-			if (Z_TYPE_P(return_value) != IS_BOOL || Z_BVAL_P(return_value)) {
+			if (Z_TYPE_P(return_value) != IS_FALSE) {
 				break;
 			}
 		}
 	}
 
 	/* execute all requests */
-	mmc_pool_run(pool TSRMLS_CC);
+	mmc_pool_run(pool);
 }
 /* }}} */
 
@@ -1798,53 +1802,55 @@ PHP_FUNCTION(memcache_get_stats)
 PHP_FUNCTION(memcache_get_extended_stats)
 {
 	mmc_pool_t *pool;
-	zval *mmc_object = getThis(), *stats;
+	zval *mmc_object = getThis();
 
 	char *host, *type = NULL;
-	int i, host_len, type_len = 0;
-	long slabid = 0, limit = MMC_DEFAULT_CACHEDUMP_LIMIT;
+	int i;
+	size_t host_len, type_len = 0;
+	zend_long slabid = 0, limit = MMC_DEFAULT_CACHEDUMP_LIMIT;
 	mmc_request_t *request;
 
 	if (mmc_object == NULL) {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O|sll", &mmc_object, memcache_pool_ce, &type, &type_len, &slabid, &limit) == FAILURE) {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "O|sll", &mmc_object, memcache_pool_ce, &type, &type_len, &slabid, &limit) == FAILURE) {
 			return;
 		}
 	}
 	else {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|sll", &type, &type_len, &slabid, &limit) == FAILURE) {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "|sll", &type, &type_len, &slabid, &limit) == FAILURE) {
 			return;
 		}
 	}
 
-	if (!mmc_get_pool(mmc_object, &pool TSRMLS_CC) || !pool->num_servers) {
+	if (!mmc_get_pool(mmc_object, &pool) || !pool->num_servers) {
 		RETURN_FALSE;
 	}
 
 	if (!mmc_stats_checktype(type)) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid stats type");
+		php_error_docref(NULL, E_WARNING, "Invalid stats type");
 		RETURN_FALSE;
 	}
 
 	array_init(return_value);
 
 	for (i=0; i<pool->num_servers; i++) {
-		MAKE_STD_ZVAL(stats);
-		ZVAL_FALSE(stats);
+		zval new_stats;
+		zval *stats;
+		ZVAL_FALSE(&new_stats);
 
 		host_len = spprintf(&host, 0, "%s:%u", pool->servers[i]->host, pool->servers[i]->tcp.port);
-		add_assoc_zval_ex(return_value, host, host_len + 1, stats);
+		stats = zend_symtable_str_update(Z_ARRVAL_P(return_value), host, host_len, &new_stats);
 		efree(host);
 
-		request = mmc_pool_request(pool, MMC_PROTO_TCP, mmc_stats_handler, stats, NULL, NULL TSRMLS_CC);
+		request = mmc_pool_request(pool, MMC_PROTO_TCP, mmc_stats_handler, stats, NULL, NULL);
 		pool->protocol->stats(request, type, slabid, limit);
 
-		if (mmc_pool_schedule(pool, pool->servers[i], request TSRMLS_CC) == MMC_OK) {
-			mmc_pool_run(pool TSRMLS_CC);			
+		if (mmc_pool_schedule(pool, pool->servers[i], request) == MMC_OK) {
+			mmc_pool_run(pool);
 		}
 	}
 
 	/* execute all requests */
-	mmc_pool_run(pool TSRMLS_CC);
+	mmc_pool_run(pool);
 }
 /* }}} */
 
@@ -1854,33 +1860,33 @@ PHP_FUNCTION(memcache_set_compress_thres
 {
 	mmc_pool_t *pool;
 	zval *mmc_object = getThis();
-	long threshold;
+	zend_long threshold;
 	double min_savings = MMC_DEFAULT_SAVINGS;
 
 	if (mmc_object == NULL) {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Ol|d", &mmc_object, memcache_pool_ce, &threshold, &min_savings) == FAILURE) {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "Ol|d", &mmc_object, memcache_pool_ce, &threshold, &min_savings) == FAILURE) {
 			return;
 		}
 	}
 	else {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|d", &threshold, &min_savings) == FAILURE) {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "l|d", &threshold, &min_savings) == FAILURE) {
 			return;
 		}
 	}
 
-	if (!mmc_get_pool(mmc_object, &pool TSRMLS_CC)) {
+	if (!mmc_get_pool(mmc_object, &pool)) {
 		RETURN_FALSE;
 	}
 
 	if (threshold < 0) {
-		php_error_docref(NULL TSRMLS_CC, E_WARNING, "threshold must be a positive integer");
+		php_error_docref(NULL, E_WARNING, "threshold must be a positive integer");
 		RETURN_FALSE;
 	}
 	pool->compress_threshold = threshold;
 
 	if (min_savings != MMC_DEFAULT_SAVINGS) {
 		if (min_savings < 0 || min_savings > 1) {
-			php_error_docref(NULL TSRMLS_CC, E_WARNING, "min_savings must be a float in the 0..1 range");
+			php_error_docref(NULL, E_WARNING, "min_savings must be a float in the 0..1 range");
 			RETURN_FALSE;
 		}
 		pool->min_compress_savings = min_savings;
@@ -1925,21 +1931,21 @@ PHP_FUNCTION(memcache_close)
 	zval *mmc_object = getThis();
 
 	if (mmc_object == NULL) {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &mmc_object, memcache_pool_ce) == FAILURE) {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "O", &mmc_object, memcache_pool_ce) == FAILURE) {
 			return;
 		}
 	}
 
-	if (!mmc_get_pool(mmc_object, &pool TSRMLS_CC)) {
+	if (!mmc_get_pool(mmc_object, &pool)) {
 		RETURN_FALSE;
 	}
 
-	mmc_pool_close(pool TSRMLS_CC);
+	mmc_pool_close(pool);
 	RETURN_TRUE;
 }
 /* }}} */
 
-static int mmc_flush_handler(mmc_t *mmc, mmc_request_t *request, int response, const char *message, unsigned int message_len, void *param TSRMLS_DC) /*
+static int mmc_flush_handler(mmc_t *mmc, mmc_request_t *request, int response, const char *message, unsigned int message_len, void *param) /*
 	parses the OK response line, param is an int pointer to increment on success {{{ */
 {
 	if (response == MMC_OK) {
@@ -1949,15 +1955,15 @@ static int mmc_flush_handler(mmc_t *mmc,
 
 	if (response == MMC_RESPONSE_CLIENT_ERROR) {
 		ZVAL_FALSE((zval *)param);
-		php_error_docref(NULL TSRMLS_CC, E_NOTICE, 
+		php_error_docref(NULL, E_NOTICE,
 				"Server %s (tcp %d, udp %d) failed with: %s (%d)",
-				mmc->host, mmc->tcp.port, 
+				mmc->host, mmc->tcp.port,
 				mmc->udp.port, message, response);
 
 		return MMC_REQUEST_DONE;
 	}
 
-	return mmc_request_failure(mmc, request->io, message, message_len, 0 TSRMLS_CC);
+	return mmc_request_failure(mmc, request->io, message, message_len, 0);
 }
 /* }}} */
 
@@ -1970,35 +1976,35 @@ PHP_FUNCTION(memcache_flush)
 
 	mmc_request_t *request;
 	unsigned int i, responses = 0;
-	long delay = 0;
+	zend_long delay = 0;
 
 	if (mmc_object == NULL) {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O|l", &mmc_object, memcache_pool_ce, &delay) == FAILURE) {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "O|l", &mmc_object, memcache_pool_ce, &delay) == FAILURE) {
 			return;
 		}
 	}
 	else {
-		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &delay) == FAILURE) {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "|l", &delay) == FAILURE) {
 			return;
 		}
 	}
 
-	if (!mmc_get_pool(mmc_object, &pool TSRMLS_CC)) {
+	if (!mmc_get_pool(mmc_object, &pool)) {
 		RETURN_FALSE;
 	}
 
 	for (i=0; i<pool->num_servers; i++) {
-		request = mmc_pool_request(pool, MMC_PROTO_TCP, mmc_flush_handler, &responses, NULL, NULL TSRMLS_CC);
+		request = mmc_pool_request(pool, MMC_PROTO_TCP, mmc_flush_handler, &responses, NULL, NULL);
 		pool->protocol->flush(request, delay);
 
-		if (mmc_pool_schedule(pool, pool->servers[i], request TSRMLS_CC) == MMC_OK) {
+		if (mmc_pool_schedule(pool, pool->servers[i], request) == MMC_OK) {
 			/* begin sending requests immediatly */
-			mmc_pool_select(pool TSRMLS_CC);
+			mmc_pool_select(pool);
 		}
 	}
 
 	/* execute all requests */
-	mmc_pool_run(pool TSRMLS_CC);
+	mmc_pool_run(pool);
 
 	if (responses < pool->num_servers) {
 		RETURN_FALSE;
@@ -2007,10 +2013,39 @@ PHP_FUNCTION(memcache_flush)
 }
 /* }}} */
 
+/* {{{ proto string memcache_set_sasl_data(object memcache, string username, string password)
+   Set credentials for sals authentification */
+PHP_FUNCTION(memcache_set_sasl_auth_data)
+{
+	zval *mmc_object = getThis();
+	char *user;
+	size_t user_length;
+	char *password;
+	size_t password_length;
+
+	if (mmc_object == NULL) {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "Oss", &mmc_object, memcache_pool_ce, &user, &user_length, &password, &password_length) == FAILURE) {
+			return;
+		}
+	} else {
+		if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &user, &user_length, &password, &password_length) == FAILURE) {
+			return;
+		}
+	}
+	if (user_length < 1 || password_length < 1) {
+		RETURN_FALSE;
+	}
+	zend_update_property_stringl(memcache_pool_ce, mmc_object, "username", strlen("username"), user, user_length);
+	zend_update_property_stringl(memcache_pool_ce, mmc_object, "password", strlen("password"), password, password_length);
+	RETURN_TRUE;
+}
+/* }}} */
+
+
 /* {{{ proto bool memcache_debug( bool onoff ) */
 PHP_FUNCTION(memcache_debug)
 {
-	php_error_docref(NULL TSRMLS_CC, E_WARNING, "memcache_debug() is deprecated, please use a debugger (like Eclipse + CDT)");
+	php_error_docref(NULL, E_WARNING, "memcache_debug() is deprecated, please use a debugger (like Eclipse + CDT)");
 }
 /* }}} */
 
