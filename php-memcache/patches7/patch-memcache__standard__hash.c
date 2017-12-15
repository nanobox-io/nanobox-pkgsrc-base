$NetBSD$

--- memcache_standard_hash.c.orig	2013-04-08 02:12:54.000000000 +0000
+++ memcache_standard_hash.c
@@ -38,7 +38,7 @@ typedef struct mmc_standard_state {
 void *mmc_standard_create_state(mmc_hash_function_t *hash) /* {{{ */
 {
 	mmc_standard_state_t *state = emalloc(sizeof(mmc_standard_state_t));
-	memset(state, 0, sizeof(mmc_standard_state_t));
+	ZEND_SECURE_ZERO(state, sizeof(mmc_standard_state_t));
 	state->hash = hash;
 	return state;
 }
@@ -56,7 +56,7 @@ void mmc_standard_free_state(void *s) /*
 }
 /* }}} */
 
-mmc_t *mmc_standard_find_server(void *s, const char *key, unsigned int key_len TSRMLS_DC) /* {{{ */
+mmc_t *mmc_standard_find_server(void *s, const char *key, unsigned int key_len) /* {{{ */
 {
 	mmc_standard_state_t *state = s;
 
