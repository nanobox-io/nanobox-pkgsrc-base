$NetBSD$

--- php_memcache.h.orig	2013-04-08 02:12:54.000000000 +0000
+++ php_memcache.h
@@ -64,25 +64,23 @@ PHP_FUNCTION(memcache_increment);
 PHP_FUNCTION(memcache_decrement);
 PHP_FUNCTION(memcache_close);
 PHP_FUNCTION(memcache_flush);
+PHP_FUNCTION(memcache_set_sasl_auth_data);
 
-#define PHP_MEMCACHE_VERSION "3.0.8"
+#define PHP_MEMCACHE_VERSION "3.0.9-dev"
 
 #define MMC_DEFAULT_TIMEOUT 1				/* seconds */
 #define MMC_DEFAULT_RETRY 15 				/* retry failed server after x seconds */
 #define MMC_DEFAULT_CACHEDUMP_LIMIT	100		/* number of entries */
 
-#if (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION >= 3)
-#   define IS_CALLABLE(cb_zv, flags, cb_sp) zend_is_callable((cb_zv), (flags), (cb_sp) TSRMLS_CC)
-#else
-#   define IS_CALLABLE(cb_zv, flags, cb_sp) zend_is_callable((cb_zv), (flags), (cb_sp))
-#endif
+#define MEMCACHE_IS_CALLABLE(cb_zv, flags, cb_sp) zend_is_callable((cb_zv), (flags), (cb_sp))
+#define MEMCACHE_LIST_INSERT(list, val) zend_list_insert((list), (val))
 
 /* internal functions */
-mmc_t *mmc_find_persistent(const char *, int, unsigned short, unsigned short, double, int TSRMLS_DC);
-int mmc_value_handler_single(const char *, unsigned int, zval *, unsigned int, unsigned long, void * TSRMLS_DC);
-int mmc_value_handler_multi(const char *, unsigned int, zval *, unsigned int, unsigned long, void * TSRMLS_DC);
-int mmc_stored_handler(mmc_t *, mmc_request_t *, int, const char *, unsigned int, void * TSRMLS_DC);
-int mmc_numeric_response_handler(mmc_t *, mmc_request_t *, int, const char *, unsigned int, void * TSRMLS_DC);
+mmc_t *mmc_find_persistent(const char *, int, unsigned short, unsigned short, double, int);
+int mmc_value_handler_single(const char *, unsigned int, zval *, unsigned int, unsigned long, void *);
+int mmc_value_handler_multi(const char *, unsigned int, zval *, unsigned int, unsigned long, void *);
+int mmc_stored_handler(mmc_t *, mmc_request_t *, int, const char *, unsigned int, void *);
+int mmc_numeric_response_handler(mmc_t *, mmc_request_t *, int, const char *, unsigned int, void *);
 
 /* session handler struct */
 #if HAVE_MEMCACHE_SESSION
