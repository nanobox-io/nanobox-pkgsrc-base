$NetBSD$

--- zbar/decoder/ean.c.orig	2009-10-23 18:16:44.000000000 +0000
+++ zbar/decoder/ean.c
@@ -121,23 +121,23 @@ static inline signed char aux_end (zbar_
     /* check quiet zone */
     unsigned qz = get_width(dcode, 0);
     if(!fwd && qz && qz < s * 3 / 4) {
-        dprintf(2, " [invalid quiet]");
+        zbar_dprintf(2, " [invalid quiet]");
         return(-1);
     }
 
-    dprintf(2, " (");
+    zbar_dprintf(2, " (");
     signed char code = 0;
     unsigned char i;
     for(i = 1 - fwd; i < 3 + fwd; i++) {
         unsigned e = get_width(dcode, i) + get_width(dcode, i + 1);
-        dprintf(2, " %d", e);
+        zbar_dprintf(2, " %d", e);
         code = (code << 2) | decode_e(e, s, 7);
         if(code < 0) {
-            dprintf(2, " [invalid end guard]");
+            zbar_dprintf(2, " [invalid end guard]");
             return(-1);
         }
     }
-    dprintf(2, ") s=%d aux=%x", s, code);
+    zbar_dprintf(2, ") s=%d aux=%x", s, code);
     return(code);
 }
 
@@ -149,7 +149,7 @@ static inline signed char aux_start (zba
     /* FIXME NB add-on has no guard in reverse */
     unsigned e2 = get_width(dcode, 5) + get_width(dcode, 6);
     if(decode_e(e2, dcode->ean.s4, 7)) {
-        dprintf(2, " [invalid any]");
+        zbar_dprintf(2, " [invalid any]");
         return(/*FIXME (get_color(dcode) == ZBAR_SPACE) ? STATE_ADDON : */-1);
     }
 
@@ -161,15 +161,15 @@ static inline signed char aux_start (zba
         unsigned qz = get_width(dcode, 7);
         if(!qz || qz >= dcode->ean.s4 * 3 / 4) {
             if(!E1) {
-                dprintf(2, " [valid normal]");
+                zbar_dprintf(2, " [valid normal]");
                 return(0); /* normal symbol start */
             }
             else if(E1 == 1) {
-                dprintf(2, " [valid add-on]");
+                zbar_dprintf(2, " [valid add-on]");
                 return(STATE_ADDON); /* add-on symbol start */
             }
         }
-        dprintf(2, " [invalid start]");
+        zbar_dprintf(2, " [invalid start]");
         return(-1);
     }
 
@@ -177,11 +177,11 @@ static inline signed char aux_start (zba
         /* attempting decode from SPACE => validate center guard */
         unsigned e3 = get_width(dcode, 6) + get_width(dcode, 7);
         if(!decode_e(e3, dcode->ean.s4, 7)) {
-            dprintf(2, " [valid center]");
+            zbar_dprintf(2, " [valid center]");
             return(0); /* start after center guard */
         }
     }
-    dprintf(2, " [invalid center]");
+    zbar_dprintf(2, " [invalid center]");
     return(/*STATE_ADDON*/-1);
 }
 
@@ -193,14 +193,14 @@ static inline signed char decode4 (zbar_
                    ? get_width(dcode, 0) + get_width(dcode, 1)
                    : get_width(dcode, 2) + get_width(dcode, 3));
     unsigned e2 = get_width(dcode, 1) + get_width(dcode, 2);
-    dprintf(2, "\n        e1=%d e2=%d", e1, e2);
+    zbar_dprintf(2, "\n        e1=%d e2=%d", e1, e2);
 
     /* create compacted encoding for direct lookup */
     signed char code = ((decode_e(e1, dcode->ean.s4, 7) << 2) |
                         decode_e(e2, dcode->ean.s4, 7));
     if(code < 0)
         return(-1);
-    dprintf(2, " code=%x", code);
+    zbar_dprintf(2, " code=%x", code);
 
     /* 4 combinations require additional determinant (D2)
        E1E2 == 34 (0110)
@@ -220,9 +220,9 @@ static inline signed char decode4 (zbar_
         unsigned char alt = d2 > (mid * dcode->ean.s4);
         if(alt)
             code = ((code >> 1) & 3) | 0x10; /* compress code space */
-        dprintf(2, " (d2=%d(%d) alt=%d)", d2, mid * dcode->ean.s4, alt);
+        zbar_dprintf(2, " (d2=%d(%d) alt=%d)", d2, mid * dcode->ean.s4, alt);
     }
-    dprintf(2, " char=%02x", digits[(unsigned char)code]);
+    zbar_dprintf(2, " char=%02x", digits[(unsigned char)code]);
     zassert(code < 0x14, -1, "code=%02x e1=%x e2=%x s4=%x color=%x\n",
             code, e1, e2, dcode->ean.s4, get_color(dcode));
     return(code);
@@ -237,7 +237,7 @@ static inline zbar_symbol_type_t ean_par
                          (pass->raw[3] & 0x10) >> 3 |
                          (pass->raw[4] & 0x10) >> 4);
 
-    dprintf(2, " par=%x", par);
+    zbar_dprintf(2, " par=%x", par);
     if(par && par != 0xf)
         /* invalid parity combination */
         return(ZBAR_NONE);
@@ -252,8 +252,8 @@ static inline zbar_symbol_type_t ean_par
         pass->raw[3] = tmp;
     }
 
-    dprintf(2, "\n");
-    dprintf(1, "decode4=%x%x%x%x\n",
+    zbar_dprintf(2, "\n");
+    zbar_dprintf(1, "decode4=%x%x%x%x\n",
             pass->raw[1] & 0xf, pass->raw[2] & 0xf,
             pass->raw[3] & 0xf, pass->raw[4] & 0xf);
     if(!par)
@@ -285,7 +285,7 @@ static inline zbar_symbol_type_t ean_par
     if(par & 1)
         pass->raw[0] >>= 4;
     pass->raw[0] &= 0xf;
-    dprintf(2, " par=%02x(%x)", par, pass->raw[0]);
+    zbar_dprintf(2, " par=%02x(%x)", par, pass->raw[0]);
 
     if(pass->raw[0] == 0xf)
         /* invalid parity combination */
@@ -301,8 +301,8 @@ static inline zbar_symbol_type_t ean_par
         }
     }
 
-    dprintf(2, "\n");
-    dprintf(1, "decode=%x%x%x%x%x%x%x(%02x)\n",
+    zbar_dprintf(2, "\n");
+    zbar_dprintf(1, "decode=%x%x%x%x%x%x%x(%02x)\n",
             pass->raw[0] & 0xf, pass->raw[1] & 0xf,
             pass->raw[2] & 0xf, pass->raw[3] & 0xf,
             pass->raw[4] & 0xf, pass->raw[5] & 0xf,
@@ -332,7 +332,7 @@ static inline zbar_symbol_type_t decode_
        (idx == 0x10 || idx == 0x11) &&
        TEST_CFG(dcode->ean.ean8_config, ZBAR_CFG_ENABLE) &&
        !aux_end(dcode, fwd)) {
-        dprintf(2, " fwd=%x", fwd);
+        zbar_dprintf(2, " fwd=%x", fwd);
         zbar_symbol_type_t part = ean_part_end4(pass, fwd);
         pass->state = -1;
         return(part);
@@ -352,10 +352,10 @@ static inline zbar_symbol_type_t decode_
         if(code < 0)
             pass->state = -1;
         else {
-            dprintf(2, "\n        raw[%x]=%02x =>", idx >> 2,
+            zbar_dprintf(2, "\n        raw[%x]=%02x =>", idx >> 2,
                     digits[(unsigned char)code]);
             pass->raw[(idx >> 2) + 1] = digits[(unsigned char)code];
-            dprintf(2, " raw=%d%d%d%d%d%d%d",
+            zbar_dprintf(2, " raw=%d%d%d%d%d%d%d",
                     pass->raw[0] & 0xf, pass->raw[1] & 0xf,
                     pass->raw[2] & 0xf, pass->raw[3] & 0xf,
                     pass->raw[4] & 0xf, pass->raw[5] & 0xf,
@@ -366,7 +366,7 @@ static inline zbar_symbol_type_t decode_
     if(get_color(dcode) == ZBAR_SPACE &&
        (idx == 0x18 || idx == 0x19)) {
         zbar_symbol_type_t part = ZBAR_NONE;
-        dprintf(2, " fwd=%x", fwd);
+        zbar_dprintf(2, " fwd=%x", fwd);
         if(!aux_end(dcode, fwd))
             part = ean_part_end7(&dcode->ean, pass, fwd);
         pass->state = -1;
@@ -401,7 +401,7 @@ static inline signed char ean_verify_che
     zassert(d < 10, -1, "n=%x d=%x chk=%x %s\n", n, d, chk,
             _zbar_decoder_buf_dump((void*)ean->buf, 18));
     if(chk != d) {
-        dprintf(1, "\nchecksum mismatch %d != %d (%s)\n",
+        zbar_dprintf(1, "\nchecksum mismatch %d != %d (%s)\n",
                 chk, d, dsprintbuf(ean));
         return(-1);
     }
@@ -455,7 +455,7 @@ static inline zbar_symbol_type_t integra
 {
     /* copy raw data into holding buffer */
     /* if same partial is not consistent, reset others */
-    dprintf(2, " integrate part=%x (%s)", part, dsprintbuf(ean));
+    zbar_dprintf(2, " integrate part=%x (%s)", part, dsprintbuf(ean));
     signed char i, j;
     if(part & ZBAR_ADDON) {
         /* FIXME TBD */
@@ -473,7 +473,7 @@ static inline zbar_symbol_type_t integra
         if((ean->left && ((part & ZBAR_SYMBOL) != ean->left)) ||
            (ean->right && ((part & ZBAR_SYMBOL) != ean->right))) {
             /* partial mismatch - reset collected parts */
-            dprintf(2, " rst(type %x %x)", ean->left, ean->right);
+            zbar_dprintf(2, " rst(type %x %x)", ean->left, ean->right);
             ean->left = ean->right = ean->addon = ZBAR_NONE;
         }
 
@@ -484,7 +484,7 @@ static inline zbar_symbol_type_t integra
                 unsigned char digit = pass->raw[i] & 0xf;
                 if(ean->right && ean->buf[j] != digit) {
                     /* partial mismatch - reset collected parts */
-                    dprintf(2, " rst(right)");
+                    zbar_dprintf(2, " rst(right)");
                     ean->left = ean->right = ean->addon = ZBAR_NONE;
                 }
                 ean->buf[j] = digit;
@@ -497,7 +497,7 @@ static inline zbar_symbol_type_t integra
                 unsigned char digit = pass->raw[i] & 0xf;
                 if(ean->left && ean->buf[j] != digit) {
                     /* partial mismatch - reset collected parts */
-                    dprintf(2, " rst(left)");
+                    zbar_dprintf(2, " rst(left)");
                     ean->left = ean->right = ean->addon = ZBAR_NONE;
                 }
                 ean->buf[j] = digit;
@@ -556,7 +556,7 @@ static inline zbar_symbol_type_t integra
     if(part > ZBAR_PARTIAL)
         part |= ean->addon;
 
-    dprintf(2, " %x/%x=%x", ean->left, ean->right, part);
+    zbar_dprintf(2, " %x/%x=%x", ean->left, ean->right, part);
     return(part);
 }
 
@@ -614,7 +614,7 @@ zbar_symbol_type_t _zbar_decode_ean (zba
         if(pass->state >= 0 ||
            i == pass_idx)
         {
-            dprintf(2, "      ean[%x/%x]: idx=%x st=%d s=%d",
+            zbar_dprintf(2, "      ean[%x/%x]: idx=%x st=%d s=%d",
                     pass_idx, i, dcode->idx, pass->state, dcode->ean.s4);
             zbar_symbol_type_t part = decode_pass(dcode, pass);
             if(part) {
@@ -622,20 +622,20 @@ zbar_symbol_type_t _zbar_decode_ean (zba
                 sym = integrate_partial(&dcode->ean, pass, part);
                 if(sym) {
                     /* this pass valid => _reset_ all passes */
-                    dprintf(2, " sym=%x", sym);
+                    zbar_dprintf(2, " sym=%x", sym);
                     dcode->ean.pass[0].state = dcode->ean.pass[1].state = -1;
                     dcode->ean.pass[2].state = dcode->ean.pass[3].state = -1;
                     if(sym > ZBAR_PARTIAL) {
                         if(!get_lock(dcode, ZBAR_EAN13))
                             postprocess(dcode, sym);
                         else {
-                            dprintf(1, " [locked %d]", dcode->lock);
+                            zbar_dprintf(1, " [locked %d]", dcode->lock);
                             sym = ZBAR_PARTIAL;
                         }
                     }
                 }
             }
-            dprintf(2, "\n");
+            zbar_dprintf(2, "\n");
         }
     }
     return(sym);
