$NetBSD$

--- zbar/decoder.c.orig	2009-10-23 18:16:44.000000000 +0000
+++ zbar/decoder.c
@@ -178,7 +178,7 @@ zbar_symbol_type_t zbar_decode_width (zb
                                       unsigned w)
 {
     dcode->w[dcode->idx & (DECODE_WINDOW - 1)] = w;
-    dprintf(1, "    decode[%x]: w=%d (%g)\n", dcode->idx, w, (w / 32.));
+    zbar_dprintf(1, "    decode[%x]: w=%d (%g)\n", dcode->idx, w, (w / 32.));
 
     /* each decoder processes width stream in parallel */
     zbar_symbol_type_t sym = dcode->type = ZBAR_NONE;
