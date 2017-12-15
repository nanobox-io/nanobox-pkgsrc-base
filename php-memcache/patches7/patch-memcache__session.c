$NetBSD$

--- memcache_session.c.orig	2013-04-08 02:12:54.000000000 +0000
+++ memcache_session.c
@@ -29,23 +29,13 @@
 #include "php_variables.h"
 
 #include "SAPI.h"
-#include "ext/standard/php_smart_str.h"
+#include "ext/standard/php_smart_string.h"
 #include "ext/standard/url.h"
-#include "php_memcache.h"
-
+#include "session/php_session.h"
 #ifdef PHP_WIN32
-void usleep(int waitTime) { 
-    __int64 time1 = 0, time2 = 0, freq = 0; 
-	 
-	QueryPerformanceCounter((LARGE_INTEGER *) &time1); 
-	QueryPerformanceFrequency((LARGE_INTEGER *)&freq); 
-			  
-	do { 
-		QueryPerformanceCounter((LARGE_INTEGER *) &time2); 
-	} while((time2-time1) < waitTime); 
-} 
-
+#include "win32/time.h"
 #endif
+#include "php_memcache.h"
 
 ZEND_EXTERN_MODULE_GLOBALS(memcache)
 
@@ -61,10 +51,10 @@ PS_OPEN_FUNC(memcache)
 	mmc_t *mmc;
 
 	php_url *url;
-	zval *params, **param;
+	zval params, *param;
 	int i, j, path_len;
 
-	pool = mmc_pool_new(TSRMLS_C);
+	pool = mmc_pool_new();
 
 	for (i=0,j=0,path_len=strlen(save_path); i<path_len; i=j+1) {
 		/* find beginning of url */
@@ -79,7 +69,8 @@ PS_OPEN_FUNC(memcache)
 		}
 
 		if (i < j) {
-			int persistent = 0, udp_port = 0, weight = 1, timeout = MMC_DEFAULT_TIMEOUT, retry_interval = MMC_DEFAULT_RETRY;
+			int persistent = 0, udp_port = 0, weight = 1, retry_interval = MMC_DEFAULT_RETRY;
+			double timeout = MMC_DEFAULT_TIMEOUT;
 
 			/* translate unix: into file: */
 			if (!strncmp(save_path+i, "unix:", sizeof("unix:")-1)) {
@@ -90,50 +81,52 @@ PS_OPEN_FUNC(memcache)
 				efree(path);
 			}
 			else {
-				url = php_url_parse_ex(save_path+i, j-i);
+				int len = j-i;
+                		char *path = estrndup(save_path+i, len);
+                		url = php_url_parse_ex(path, strlen(path));
+                		efree(path);
 			}
 
 			if (!url) {
 				char *path = estrndup(save_path+i, j-i);
-				php_error_docref(NULL TSRMLS_CC, E_WARNING,
+				php_error_docref(NULL, E_WARNING,
 					"Failed to parse session.save_path (error at offset %d, url was '%s')", i, path);
 				efree(path);
 
-				mmc_pool_free(pool TSRMLS_CC);
+				mmc_pool_free(pool);
 				PS_SET_MOD_DATA(NULL);
 				return FAILURE;
 			}
 
 			/* parse parameters */
 			if (url->query != NULL) {
-				MAKE_STD_ZVAL(params);
-				array_init(params);
+				array_init(&params);
 
-				sapi_module.treat_data(PARSE_STRING, estrdup(url->query), params TSRMLS_CC);
+				sapi_module.treat_data(PARSE_STRING, estrdup(url->query), &params);
 
-				if (zend_hash_find(Z_ARRVAL_P(params), "persistent", sizeof("persistent"), (void **) &param) != FAILURE) {
+				if ((param = zend_hash_str_find(Z_ARRVAL(params), "persistent", sizeof("persistent")-1)) != NULL) {
 					convert_to_boolean_ex(param);
-					persistent = Z_BVAL_PP(param);
+					persistent = Z_TYPE_P(param) == IS_TRUE;
 				}
 
-				if (zend_hash_find(Z_ARRVAL_P(params), "udp_port", sizeof("udp_port"), (void **) &param) != FAILURE) {
+				if ((param = zend_hash_str_find(Z_ARRVAL(params), "udp_port", sizeof("udp_port")-1)) != NULL) {
 					convert_to_long_ex(param);
-					udp_port = Z_LVAL_PP(param);
+					udp_port = Z_LVAL_P(param);
 				}
 
-				if (zend_hash_find(Z_ARRVAL_P(params), "weight", sizeof("weight"), (void **) &param) != FAILURE) {
+				if ((param = zend_hash_str_find(Z_ARRVAL(params), "weight", sizeof("weight")-1)) != NULL) {
 					convert_to_long_ex(param);
-					weight = Z_LVAL_PP(param);
+					weight = Z_LVAL_P(param);
 				}
 
-				if (zend_hash_find(Z_ARRVAL_P(params), "timeout", sizeof("timeout"), (void **) &param) != FAILURE) {
-					convert_to_long_ex(param);
-					timeout = Z_LVAL_PP(param);
+				if ((param = zend_hash_str_find(Z_ARRVAL(params), "timeout", sizeof("timeout")-1)) != NULL) {
+					convert_to_double_ex(param);
+					timeout = Z_DVAL_P(param);
 				}
 
-				if (zend_hash_find(Z_ARRVAL_P(params), "retry_interval", sizeof("retry_interval"), (void **) &param) != FAILURE) {
+				if ((param = zend_hash_str_find(Z_ARRVAL(params), "retry_interval", sizeof("retry_interval")-1)) != NULL) {
 					convert_to_long_ex(param);
-					retry_interval = Z_LVAL_PP(param);
+					retry_interval = Z_LVAL_P(param);
 				}
 
 				zval_ptr_dtor(&params);
@@ -149,10 +142,10 @@ PS_OPEN_FUNC(memcache)
 				}
 
 				if (persistent) {
-					mmc = mmc_find_persistent(host, host_len, 0, 0, timeout, retry_interval TSRMLS_CC);
+					mmc = mmc_find_persistent(host, host_len, 0, 0, timeout, retry_interval);
 				}
 				else {
-					mmc = mmc_server_new(host, host_len, 0, 0, 0, timeout, retry_interval TSRMLS_CC);
+					mmc = mmc_server_new(host, host_len, 0, 0, 0, timeout, retry_interval);
 				}
 
 				efree(host);
@@ -160,16 +153,16 @@ PS_OPEN_FUNC(memcache)
 			else {
 				if (url->host == NULL || weight <= 0 || timeout <= 0) {
 					php_url_free(url);
-					mmc_pool_free(pool TSRMLS_CC);
+					mmc_pool_free(pool);
 					PS_SET_MOD_DATA(NULL);
 					return FAILURE;
 				}
 
 				if (persistent) {
-					mmc = mmc_find_persistent(url->host, strlen(url->host), url->port, udp_port, timeout, retry_interval TSRMLS_CC);
+					mmc = mmc_find_persistent(url->host, strlen(url->host), url->port, udp_port, timeout, retry_interval);
 				}
 				else {
-					mmc = mmc_server_new(url->host, strlen(url->host), url->port, udp_port, 0, timeout, retry_interval TSRMLS_CC);
+					mmc = mmc_server_new(url->host, strlen(url->host), url->port, udp_port, 0, timeout, retry_interval);
 				}
 			}
 
@@ -183,7 +176,7 @@ PS_OPEN_FUNC(memcache)
 		return SUCCESS;
 	}
 
-	mmc_pool_free(pool TSRMLS_CC);
+	mmc_pool_free(pool);
 	PS_SET_MOD_DATA(NULL);
 	return FAILURE;
 }
@@ -196,7 +189,7 @@ PS_CLOSE_FUNC(memcache)
 	mmc_pool_t *pool = PS_GET_MOD_DATA();
 
 	if (pool) {
-		mmc_pool_free(pool TSRMLS_CC);
+		mmc_pool_free(pool);
 		PS_SET_MOD_DATA(NULL);
 	}
 
@@ -206,7 +199,7 @@ PS_CLOSE_FUNC(memcache)
 
 static int php_mmc_session_read_request(
 	mmc_pool_t *pool, zval *zkey, zval **lockparam, zval *addparam, zval **dataparam,
-	mmc_request_t **lockreq, mmc_request_t **addreq, mmc_request_t **datareq TSRMLS_DC) /* {{{ */
+	mmc_request_t **lockreq, mmc_request_t **addreq, mmc_request_t **datareq) /* {{{ */
 {
 	mmc_request_t *lreq, *areq, *dreq;
 	zval lockvalue;
@@ -214,19 +207,19 @@ static int php_mmc_session_read_request(
 	/* increment request which stores the response int using value_handler_single */
 	lreq = mmc_pool_request(
 		pool, MMC_PROTO_TCP, mmc_numeric_response_handler, lockparam[0],
-		mmc_pool_failover_handler_null, NULL TSRMLS_CC);
+		mmc_pool_failover_handler_null, NULL);
 	lreq->value_handler = mmc_value_handler_single;
 	lreq->value_handler_param = lockparam;
 
 	/* add request which should fail if lock has been incremented */
 	areq = mmc_pool_request(
 		pool, MMC_PROTO_TCP, mmc_stored_handler, addparam,
-		mmc_pool_failover_handler_null, NULL TSRMLS_CC);
+		mmc_pool_failover_handler_null, NULL);
 
 	/* request to fetch the session data */
 	dreq = mmc_pool_request_get(
 		pool, MMC_PROTO_TCP, mmc_value_handler_single, dataparam,
-		mmc_pool_failover_handler_null, NULL TSRMLS_CC);
+		mmc_pool_failover_handler_null, NULL);
 
 	/* prepare key */
 	if (mmc_prepare_key_ex(Z_STRVAL_P(zkey), Z_STRLEN_P(zkey), dreq->key, &(dreq->key_len)) != MMC_OK) {
@@ -250,7 +243,7 @@ static int php_mmc_session_read_request(
 
 	/* build requests */
 	pool->protocol->mutate(lreq, zkey, lreq->key, lreq->key_len, 1, 1, 1, MEMCACHE_G(lock_timeout));
-	pool->protocol->store(pool, areq, MMC_OP_ADD, areq->key, areq->key_len, 0, MEMCACHE_G(lock_timeout), 0, &lockvalue TSRMLS_CC);
+	pool->protocol->store(pool, areq, MMC_OP_ADD, areq->key, areq->key_len, 0, MEMCACHE_G(lock_timeout), 0, &lockvalue);
 	pool->protocol->get(dreq, MMC_OP_GET, zkey, dreq->key, dreq->key_len);
 
 	*lockreq = lreq;
@@ -285,7 +278,7 @@ PS_READ_FUNC(memcache)
 		dataparam[1] = NULL;
 		dataparam[2] = NULL;
 
-		ZVAL_STRING(&zkey, (char *)key, 0);
+		ZVAL_STR(&zkey, key);
 
 		do {
 			/* first request tries to increment lock */
@@ -299,19 +292,19 @@ PS_READ_FUNC(memcache)
 			ZVAL_NULL(&dataresult);
 
 			/* create requests */
-			if (php_mmc_session_read_request(pool, &zkey, lockparam, &addresult, dataparam, &lockrequest, &addrequest, &datarequest TSRMLS_CC) != MMC_OK) {
+			if (php_mmc_session_read_request(pool, &zkey, lockparam, &addresult, dataparam, &lockrequest, &addrequest, &datarequest) != MMC_OK) {
 				break;
 			}
 
 			/* find next server in line */
 			prev_index = last_index;
-			mmc = mmc_pool_find_next(pool, datarequest->key, datarequest->key_len, &skip_servers, &last_index TSRMLS_CC);
+			mmc = mmc_pool_find_next(pool, datarequest->key, datarequest->key_len, &skip_servers, &last_index);
 
 			/* schedule the requests */
-			if (!mmc_server_valid(mmc TSRMLS_CC) ||
-				 mmc_pool_schedule(pool, mmc, lockrequest TSRMLS_CC) != MMC_OK ||
-				 /*pool->protocol != &mmc_binary_protocol && */mmc_pool_schedule(pool, mmc, addrequest TSRMLS_CC) != MMC_OK ||
-				 mmc_pool_schedule(pool, mmc, datarequest TSRMLS_CC) != MMC_OK) {
+			if (!mmc_server_valid(mmc) ||
+				 mmc_pool_schedule(pool, mmc, lockrequest) != MMC_OK ||
+				 /*pool->protocol != &mmc_binary_protocol && */mmc_pool_schedule(pool, mmc, addrequest) != MMC_OK ||
+				 mmc_pool_schedule(pool, mmc, datarequest) != MMC_OK) {
 				mmc_pool_release(pool, lockrequest);
 				mmc_pool_release(pool, addrequest);
 				mmc_pool_release(pool, datarequest);
@@ -320,14 +313,14 @@ PS_READ_FUNC(memcache)
 			}
 
 			/* execute requests */
-			mmc_pool_run(pool TSRMLS_CC);
+			mmc_pool_run(pool);
 
-			if ((Z_TYPE(lockresult) == IS_LONG && Z_LVAL(lockresult) == 1) || (Z_TYPE(addresult) == IS_BOOL && Z_BVAL(addresult))) {
+			if ((Z_TYPE(lockresult) == IS_LONG && Z_LVAL(lockresult) == 1) || ((Z_TYPE(addresult) == IS_TRUE || Z_TYPE(addresult) == IS_FALSE) && Z_TYPE(addresult) == IS_TRUE)) {
 				if (Z_TYPE(dataresult) == IS_STRING) {
 					/* break if successfully locked with existing value */
 					mmc_queue_free(&skip_servers);
-					*val = Z_STRVAL(dataresult);
-					*vallen = Z_STRLEN(dataresult);
+					*val = zend_string_init(Z_STRVAL(dataresult), Z_STRLEN(dataresult), 1);
+					zval_ptr_dtor(&dataresult);
 					return SUCCESS;
 				}
 
@@ -378,9 +371,9 @@ PS_WRITE_FUNC(memcache)
 			/* allocate requests */
 			datarequest = mmc_pool_request(
 				pool, MMC_PROTO_TCP, mmc_stored_handler, &dataresult,
-				mmc_pool_failover_handler_null, NULL TSRMLS_CC);
+				mmc_pool_failover_handler_null, NULL);
 
-			if (mmc_prepare_key_ex(key, strlen(key), datarequest->key, &(datarequest->key_len)) != MMC_OK) {
+			if (mmc_prepare_key_ex(ZSTR_VAL(key), ZSTR_LEN(key), datarequest->key, &(datarequest->key_len)) != MMC_OK) {
 				mmc_pool_release(pool, datarequest);
 				break;
 			}
@@ -388,30 +381,30 @@ PS_WRITE_FUNC(memcache)
 			/* append .lock to key */
 			lockrequest = mmc_pool_request(
 				pool, MMC_PROTO_TCP, mmc_stored_handler, &lockresult,
-				mmc_pool_failover_handler_null, NULL TSRMLS_CC);
+				mmc_pool_failover_handler_null, NULL);
 
 			memcpy(lockrequest->key, datarequest->key, datarequest->key_len);
 			strcpy(lockrequest->key + datarequest->key_len, ".lock");
 			lockrequest->key_len = datarequest->key_len + sizeof(".lock")-1;
 
 			ZVAL_LONG(&lockvalue, 0);
-			ZVAL_STRINGL(&value, (char *)val, vallen, 0);
+			ZVAL_STR(&value, val);
 
 			/* assemble commands to store data and reset lock */
-			if (pool->protocol->store(pool, datarequest, MMC_OP_SET, datarequest->key, datarequest->key_len, 0, INI_INT("session.gc_maxlifetime"), 0, &value TSRMLS_CC) != MMC_OK ||
-				pool->protocol->store(pool, lockrequest, MMC_OP_SET, lockrequest->key, lockrequest->key_len, 0, MEMCACHE_G(lock_timeout), 0, &lockvalue TSRMLS_CC) != MMC_OK) {
+			if (pool->protocol->store(pool, datarequest, MMC_OP_SET, datarequest->key, datarequest->key_len, 0, INI_INT("session.gc_maxlifetime"), 0, &value) != MMC_OK ||
+				pool->protocol->store(pool, lockrequest, MMC_OP_SET, lockrequest->key, lockrequest->key_len, 0, MEMCACHE_G(lock_timeout), 0, &lockvalue) != MMC_OK) {
 				mmc_pool_release(pool, datarequest);
 				mmc_pool_release(pool, lockrequest);
 				break;
 			}
 
 			/* find next server in line */
-			mmc = mmc_pool_find_next(pool, datarequest->key, datarequest->key_len, &skip_servers, &last_index TSRMLS_CC);
+			mmc = mmc_pool_find_next(pool, datarequest->key, datarequest->key_len, &skip_servers, &last_index);
 			mmc_queue_push(&skip_servers, mmc);
 
-			if (!mmc_server_valid(mmc TSRMLS_CC) ||
-				 mmc_pool_schedule(pool, mmc, datarequest TSRMLS_CC) != MMC_OK ||
-				 mmc_pool_schedule(pool, mmc, lockrequest TSRMLS_CC) != MMC_OK) {
+			if (!mmc_server_valid(mmc) ||
+				 mmc_pool_schedule(pool, mmc, datarequest) != MMC_OK ||
+				 mmc_pool_schedule(pool, mmc, lockrequest) != MMC_OK) {
 				mmc_pool_release(pool, datarequest);
 				mmc_pool_release(pool, lockrequest);
 				continue;
@@ -421,9 +414,9 @@ PS_WRITE_FUNC(memcache)
 		mmc_queue_free(&skip_servers);
 
 		/* execute requests */
-		mmc_pool_run(pool TSRMLS_CC);
+		mmc_pool_run(pool);
 
-		if (Z_BVAL(lockresult) && Z_BVAL(dataresult)) {
+		if (Z_TYPE(lockresult) == IS_TRUE && Z_TYPE(dataresult) == IS_TRUE) {
 			return SUCCESS;
 		}
 	}
@@ -432,7 +425,7 @@ PS_WRITE_FUNC(memcache)
 }
 /* }}} */
 
-static int mmc_deleted_handler(mmc_t *mmc, mmc_request_t *request, int response, const char *message, unsigned int message_len, void *param TSRMLS_DC) /*
+static int mmc_deleted_handler(mmc_t *mmc, mmc_request_t *request, int response, const char *message, unsigned int message_len, void *param) /*
 	parses a DELETED response line, param is a zval pointer to store result into {{{ */
 {
 	if (response == MMC_OK || response == MMC_RESPONSE_NOT_FOUND) {
@@ -442,7 +435,7 @@ static int mmc_deleted_handler(mmc_t *mm
 
 	if (response == MMC_RESPONSE_CLIENT_ERROR) {
 		ZVAL_FALSE((zval *)param);
-		php_error_docref(NULL TSRMLS_CC, E_NOTICE, 
+		php_error_docref(NULL, E_NOTICE, 
 				"Server %s (tcp %d, udp %d) failed with: %s (%d)",
 				mmc->host, mmc->tcp.port, 
 				mmc->udp.port, message, response);
@@ -451,7 +444,7 @@ static int mmc_deleted_handler(mmc_t *mm
 	}
 
 
-	return mmc_request_failure(mmc, request->io, message, message_len, 0 TSRMLS_CC);
+	return mmc_request_failure(mmc, request->io, message, message_len, 0);
 }
 /* }}} */
 
@@ -476,9 +469,9 @@ PS_DESTROY_FUNC(memcache)
 			/* allocate requests */
 			datarequest = mmc_pool_request(
 				pool, MMC_PROTO_TCP, mmc_deleted_handler, &dataresult,
-				mmc_pool_failover_handler_null, NULL TSRMLS_CC);
+				mmc_pool_failover_handler_null, NULL);
 
-			if (mmc_prepare_key_ex(key, strlen(key), datarequest->key, &(datarequest->key_len)) != MMC_OK) {
+			if (mmc_prepare_key_ex(ZSTR_VAL(key), ZSTR_LEN(key), datarequest->key, &(datarequest->key_len)) != MMC_OK) {
 				mmc_pool_release(pool, datarequest);
 				break;
 			}
@@ -486,7 +479,7 @@ PS_DESTROY_FUNC(memcache)
 			/* append .lock to key */
 			lockrequest = mmc_pool_request(
 				pool, MMC_PROTO_TCP, mmc_deleted_handler, &lockresult,
-				mmc_pool_failover_handler_null, NULL TSRMLS_CC);
+				mmc_pool_failover_handler_null, NULL);
 
 			memcpy(lockrequest->key, datarequest->key, datarequest->key_len);
 			strcpy(lockrequest->key + datarequest->key_len, ".lock");
@@ -497,12 +490,12 @@ PS_DESTROY_FUNC(memcache)
 			pool->protocol->delete(lockrequest, lockrequest->key, lockrequest->key_len, 0);
 
 			/* find next server in line */
-			mmc = mmc_pool_find_next(pool, datarequest->key, datarequest->key_len, &skip_servers, &last_index TSRMLS_CC);
+			mmc = mmc_pool_find_next(pool, datarequest->key, datarequest->key_len, &skip_servers, &last_index);
 			mmc_queue_push(&skip_servers, mmc);
 
-			if (!mmc_server_valid(mmc TSRMLS_CC) ||
-				 mmc_pool_schedule(pool, mmc, datarequest TSRMLS_CC) != MMC_OK ||
-				 mmc_pool_schedule(pool, mmc, lockrequest TSRMLS_CC) != MMC_OK) {
+			if (!mmc_server_valid(mmc) ||
+				 mmc_pool_schedule(pool, mmc, datarequest) != MMC_OK ||
+				 mmc_pool_schedule(pool, mmc, lockrequest) != MMC_OK) {
 				mmc_pool_release(pool, datarequest);
 				mmc_pool_release(pool, lockrequest);
 				continue;
@@ -512,9 +505,9 @@ PS_DESTROY_FUNC(memcache)
 		mmc_queue_free(&skip_servers);
 
 		/* execute requests */
-		mmc_pool_run(pool TSRMLS_CC);
+		mmc_pool_run(pool);
 
-		if (Z_BVAL(lockresult) && Z_BVAL(dataresult)) {
+		if (Z_TYPE(lockresult) == IS_TRUE && Z_TYPE(dataresult) == IS_TRUE) {
 			return SUCCESS;
 		}
 	}
