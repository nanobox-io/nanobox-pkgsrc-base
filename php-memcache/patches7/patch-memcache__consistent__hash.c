$NetBSD$

--- memcache_consistent_hash.c.orig	2013-04-08 02:12:54.000000000 +0000
+++ memcache_consistent_hash.c
@@ -47,7 +47,7 @@ typedef struct mmc_consistent_state {
 void *mmc_consistent_create_state(mmc_hash_function_t *hash) /* {{{ */
 {
 	mmc_consistent_state_t *state = emalloc(sizeof(mmc_consistent_state_t));
-	memset(state, 0, sizeof(mmc_consistent_state_t));
+	ZEND_SECURE_ZERO(state, sizeof(mmc_consistent_state_t));
 	state->hash = hash;
 	return state;
 }
@@ -119,7 +119,7 @@ static void mmc_consistent_populate_buck
 }
 /* }}} */
 
-mmc_t *mmc_consistent_find_server(void *s, const char *key, unsigned int key_len TSRMLS_DC) /* {{{ */
+mmc_t *mmc_consistent_find_server(void *s, const char *key, unsigned int key_len) /* {{{ */
 {
 	mmc_consistent_state_t *state = s;
 
