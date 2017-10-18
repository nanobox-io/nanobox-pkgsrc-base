$NetBSD$

--- memcache_pool.c.orig	2013-04-08 02:12:54.000000000 +0000
+++ memcache_pool.c
@@ -44,14 +44,14 @@ inline void mmc_buffer_alloc(mmc_buffer_
 	ensures space for an additional size bytes {{{ */
 {
 	register size_t newlen;
-	smart_str_alloc((&(buffer->value)), size, 0);
+	smart_string_alloc((&(buffer->value)), size, 0);
 }
 /* }}} */
 
 inline void mmc_buffer_free(mmc_buffer_t *buffer)  /* {{{ */
 {
 	if (buffer->value.c != NULL) {
-		smart_str_free(&(buffer->value));
+		smart_string_free(&(buffer->value));
 	}
 	memset(buffer, 0, sizeof(*buffer));
 }
@@ -300,7 +300,7 @@ static void mmc_compress(mmc_pool_t *poo
 			mmc_buffer_alloc(buffer, prev.value.len + result_len);
 
 			/* append prev header */
-			smart_str_appendl(&(buffer->value), prev.value.c, prev.value.len - value_len);
+			smart_string_appendl(&(buffer->value), prev.value.c, prev.value.len - value_len);
 			buffer->idx = prev.idx;
 		}
 		else {
@@ -318,7 +318,7 @@ static void mmc_compress(mmc_pool_t *poo
 			buffer->value.len += result_len;
 		}
 		else {
-			smart_str_appendl(&(buffer->value), value, value_len);
+			smart_string_appendl(&(buffer->value), value, value_len);
 			*flags &= ~MMC_COMPRESSED;
 		}
 
@@ -327,7 +327,7 @@ static void mmc_compress(mmc_pool_t *poo
 		}
 	}
 	else if (!copy) {
-		smart_str_appendl(&(buffer->value), value, value_len);
+		smart_string_appendl(&(buffer->value), value, value_len);
 	}
 }
 /* }}}*/
@@ -369,7 +369,7 @@ int mmc_pack_value(mmc_pool_t *pool, mmc
 		case IS_LONG:
 			*flags |= MMC_TYPE_LONG;
 			*flags &= ~MMC_COMPRESSED;
-			smart_str_append_long(&(buffer->value), Z_LVAL_P(value));
+			smart_string_append_long(&(buffer->value), Z_LVAL_P(value));
 			break;
 
 		case IS_DOUBLE: {
@@ -377,14 +377,14 @@ int mmc_pack_value(mmc_pool_t *pool, mmc
 			int len = snprintf(buf, 256, "%.14g", Z_DVAL_P(value));
 			*flags |= MMC_TYPE_DOUBLE;
 			*flags &= ~MMC_COMPRESSED;
-			smart_str_appendl(&(buffer->value), buf, len);
+			smart_string_appendl(&(buffer->value), buf, len);
 			break;
 		}
 
 		case IS_BOOL:
 			*flags |= MMC_TYPE_BOOL;
 			*flags &= ~MMC_COMPRESSED;
-			smart_str_appendc(&(buffer->value), Z_BVAL_P(value) ? '1' : '0');
+			smart_string_appendc(&(buffer->value), Z_BVAL_P(value) ? '1' : '0');
 			break;
 
 		default: {
@@ -1076,7 +1076,7 @@ static inline mmc_request_t *mmc_pool_re
 
 	if (protocol == MMC_PROTO_UDP) {
 		mmc_udp_header_t header = {0};
-		smart_str_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));
+		smart_string_appendl(&(request->sendbuf.value), (const char *)&header, sizeof(header));
 	}
 
 	request->failover_handler = failover_handler != NULL ? failover_handler : mmc_pool_failover_handler_null;
