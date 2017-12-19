$NetBSD$

--- zbar/decoder/code128.c.orig	2009-10-23 18:16:44.000000000 +0000
+++ zbar/decoder/code128.c
@@ -135,7 +135,7 @@ static inline signed char decode_lo (int
     zassert(idx <= 0x50, -1, "sig=%x offset=%x base=%x idx=%x\n",
             sig, offset, base, idx);
     unsigned char c = characters[idx];
-    dprintf(2, " %02x(%x(%02x)/%x(%02x)) => %02x",
+    zbar_dprintf(2, " %02x(%x(%02x)/%x(%02x)) => %02x",
             idx, base, lo_base[base], offset, lo_offset[offset],
             (unsigned char)c);
     return(c);
@@ -149,7 +149,7 @@ static inline signed char decode_hi (int
                ((sig >>  4) & 0x00f0) |
                ((sig <<  4) & 0x0f00) |
                ((sig << 12) & 0xf000));
-    dprintf(2, " rev=%x", rev != 0);
+    zbar_dprintf(2, " rev=%x", rev != 0);
 
     unsigned char idx;
     switch(sig) {
@@ -172,7 +172,7 @@ static inline signed char decode_hi (int
     if(rev)
         idx += 0xe;
     unsigned char c = characters[0x51 + idx];
-    dprintf(2, " %02x => %02x", idx, c);
+    zbar_dprintf(2, " %02x => %02x", idx, c);
     return(c);
 }
 
@@ -192,7 +192,7 @@ static inline signed char decode6 (zbar_
 {
     /* build edge signature of character */
     unsigned s = dcode->code128.s6;
-    dprintf(2, " s=%d", s);
+    zbar_dprintf(2, " s=%d", s);
     if(s < 5)
         return(-1);
     /* calculate similar edge measurements */
@@ -207,7 +207,7 @@ static inline signed char decode6 (zbar_
            (decode_e(get_width(dcode, 2) + get_width(dcode, 1), s, 11)));
     if(sig < 0)
         return(-1);
-    dprintf(2, " sig=%04x", sig);
+    zbar_dprintf(2, " sig=%04x", sig);
     /* lookup edge signature */
     signed char c = (sig & 0x4444) ? decode_hi(sig) : decode_lo(sig);
     if(c == -1)
@@ -219,7 +219,7 @@ static inline signed char decode6 (zbar_
         : (get_width(dcode, 1) + get_width(dcode, 3) + get_width(dcode, 5));
     bars = bars * 11 * 4 / s;
     unsigned char chk = calc_check(c);
-    dprintf(2, " bars=%d chk=%d", bars, chk);
+    zbar_dprintf(2, " bars=%d chk=%d", bars, chk);
     if(chk - 7 > bars || bars > chk + 7)
         return(-1);
 
@@ -259,10 +259,10 @@ static inline unsigned char validate_che
     /* and compare to check character */
     idx = (dcode128->direction) ? 1 : dcode128->character - 2;
     unsigned char check = dcode->buf[idx];
-    dprintf(2, " chk=%02x(%02x)", sum, check);
+    zbar_dprintf(2, " chk=%02x(%02x)", sum, check);
     unsigned char err = (sum != check);
     if(err)
-        dprintf(1, " [checksum error]\n");
+        zbar_dprintf(1, " [checksum error]\n");
     return(err);
 }
 
@@ -318,12 +318,12 @@ static inline unsigned postprocess_c (zb
 static inline unsigned char postprocess (zbar_decoder_t *dcode)
 {
     code128_decoder_t *dcode128 = &dcode->code128;
-    dprintf(2, "\n    postproc len=%d", dcode128->character);
+    zbar_dprintf(2, "\n    postproc len=%d", dcode128->character);
     unsigned i, j;
     unsigned char code = 0;
     if(dcode128->direction) {
         /* reverse buffer */
-        dprintf(2, " (rev)");
+        zbar_dprintf(2, " (rev)");
         for(i = 0; i < dcode128->character / 2; i++) {
             unsigned j = dcode128->character - 1 - i;
             code = dcode->buf[i];
@@ -345,7 +345,7 @@ static inline unsigned char postprocess
 
     unsigned char charset = code - START_A;
     unsigned cexp = (code == START_C) ? 1 : 0;
-    dprintf(2, " start=%c", 'A' + charset);
+    zbar_dprintf(2, " start=%c", 'A' + charset);
 
     for(i = 1, j = 0; i < dcode128->character - 2; i++) {
         unsigned char code = dcode->buf[i];
@@ -368,7 +368,7 @@ static inline unsigned char postprocess
                 charset &= 0x7f;
         }
         else {
-            dprintf(2, " %02x", code);
+            zbar_dprintf(2, " %02x", code);
             if(charset & 0x2) {
                 /* expand character set C to ASCII */
                 zassert(cexp, 1, "i=%x j=%x code=%02x charset=%x cexp=%x %s\n",
@@ -391,7 +391,7 @@ static inline unsigned char postprocess
             else if(code == FNC1)
                 /* FIXME FNC1 - Code 128 subsets or ASCII 0x1d */;
             else if(code >= START_A) {
-                dprintf(1, " [truncated]\n");
+                zbar_dprintf(1, " [truncated]\n");
                 return(1);
             }
             else {
@@ -439,25 +439,25 @@ zbar_symbol_type_t _zbar_decode_code128
         return(0);
     dcode128->element = 0;
 
-    dprintf(2, "      code128[%c%02d+%x]:",
+    zbar_dprintf(2, "      code128[%c%02d+%x]:",
             (dcode128->direction) ? '<' : '>',
             dcode128->character, dcode128->element);
 
     signed char c = decode6(dcode);
     if(dcode128->character < 0) {
-        dprintf(2, " c=%02x", c);
+        zbar_dprintf(2, " c=%02x", c);
         if(c < START_A || c > STOP_REV || c == STOP_FWD) {
-            dprintf(2, " [invalid]\n");
+            zbar_dprintf(2, " [invalid]\n");
             return(0);
         }
         unsigned qz = get_width(dcode, 6);
         if(qz && qz < (dcode->code128.s6 * 3) / 4) {
-            dprintf(2, " [invalid qz %d]\n", qz);
+            zbar_dprintf(2, " [invalid qz %d]\n", qz);
             return(0);
         }
         /* lock shared resources */
         if(get_lock(dcode, ZBAR_CODE128)) {
-            dprintf(2, " [locked %d]\n", dcode->lock);
+            zbar_dprintf(2, " [locked %d]\n", dcode->lock);
             dcode128->character = -1;
             return(0);
         }
@@ -470,12 +470,12 @@ zbar_symbol_type_t _zbar_decode_code128
         }
         else
             dcode128->direction = ZBAR_SPACE;
-        dprintf(2, " dir=%x [valid start]", dcode128->direction);
+        zbar_dprintf(2, " dir=%x [valid start]", dcode128->direction);
     }
     else if((c < 0) ||
             ((dcode128->character >= BUFFER_MIN) &&
              size_buf(dcode, dcode128->character + 1))) {
-        dprintf(1, (c < 0) ? " [aborted]\n" : " [overflow]\n");
+        zbar_dprintf(1, (c < 0) ? " [aborted]\n" : " [overflow]\n");
         dcode->lock = 0;
         dcode128->character = -1;
         return(0);
@@ -499,17 +499,17 @@ zbar_symbol_type_t _zbar_decode_code128
         else if(dcode128->character < CFG(*dcode128, ZBAR_CFG_MIN_LEN) ||
                 (CFG(*dcode128, ZBAR_CFG_MAX_LEN) > 0 &&
                  dcode128->character > CFG(*dcode128, ZBAR_CFG_MAX_LEN))) {
-            dprintf(2, " [invalid len]\n");
+            zbar_dprintf(2, " [invalid len]\n");
             sym = ZBAR_NONE;
         }
         else
-            dprintf(2, " [valid end]\n");
+            zbar_dprintf(2, " [valid end]\n");
         dcode128->character = -1;
         if(!sym)
             dcode->lock = 0;
         return(sym);
     }
 
-    dprintf(2, "\n");
+    zbar_dprintf(2, "\n");
     return(0);
 }
