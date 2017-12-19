$NetBSD$

--- zbar/decoder/i25.c.orig	2009-10-23 18:16:44.000000000 +0000
+++ zbar/decoder/i25.c
@@ -49,7 +49,7 @@ static inline unsigned char i25_decode10
                                           unsigned char offset)
 {
     i25_decoder_t *dcode25 = &dcode->i25;
-    dprintf(2, " s=%d", dcode25->s10);
+    zbar_dprintf(2, " s=%d", dcode25->s10);
     if(dcode25->s10 < 10)
         return(0xff);
 
@@ -65,11 +65,11 @@ static inline unsigned char i25_decode10
             par++;
     }
 
-    dprintf(2, " enc=%02x par=%x", enc, par);
+    zbar_dprintf(2, " enc=%02x par=%x", enc, par);
 
     /* parity check */
     if(par != 2) {
-        dprintf(2, " [bad parity]");
+        zbar_dprintf(2, " [bad parity]");
         return(0xff);
     }
 
@@ -79,12 +79,12 @@ static inline unsigned char i25_decode10
         if(enc == 12)
             enc = 0;
         else if(--enc > 9) {
-            dprintf(2, " [invalid encoding]");
+            zbar_dprintf(2, " [invalid encoding]");
             return(0xff);
         }
     }
 
-    dprintf(2, " => %x", enc);
+    zbar_dprintf(2, " => %x", enc);
     return(enc);
 }
 
@@ -103,7 +103,7 @@ static inline signed char i25_decode_sta
     if((get_color(dcode) == ZBAR_BAR)
        ? enc != 4
        : (enc = i25_decode1(enc, get_width(dcode, i++), dcode25->s10))) {
-        dprintf(4, "      i25: s=%d enc=%x [invalid]\n", dcode25->s10, enc);
+        zbar_dprintf(4, "      i25: s=%d enc=%x [invalid]\n", dcode25->s10, enc);
         return(ZBAR_NONE);
     }
 
@@ -113,7 +113,7 @@ static inline signed char i25_decode_sta
      */
     unsigned quiet = get_width(dcode, i++);
     if(quiet && quiet < dcode25->s10 * 3 / 8) {
-        dprintf(3, "      i25: s=%d enc=%x q=%d [invalid qz]\n",
+        zbar_dprintf(3, "      i25: s=%d enc=%x q=%d [invalid qz]\n",
                 dcode25->s10, enc, quiet);
         return(ZBAR_NONE);
     }
@@ -133,7 +133,7 @@ static inline signed char i25_decode_end
     if((quiet && quiet < dcode25->width * 3 / 8) ||
        decode_e(get_width(dcode, 1), dcode25->width, 45) > 2 ||
        decode_e(get_width(dcode, 2), dcode25->width, 45) > 2) {
-        dprintf(3, " s=%d q=%d [invalid qz]\n", dcode25->width, quiet);
+        zbar_dprintf(3, " s=%d q=%d [invalid qz]\n", dcode25->width, quiet);
         return(ZBAR_NONE);
     }
 
@@ -147,7 +147,7 @@ static inline signed char i25_decode_end
 
     if(dcode25->direction) {
         /* reverse buffer */
-        dprintf(2, " (rev)");
+        zbar_dprintf(2, " (rev)");
         int i;
         for(i = 0; i < dcode25->character / 2; i++) {
             unsigned j = dcode25->character - 1 - i;
@@ -160,7 +160,7 @@ static inline signed char i25_decode_end
     if(dcode25->character < CFG(*dcode25, ZBAR_CFG_MIN_LEN) ||
        (CFG(*dcode25, ZBAR_CFG_MAX_LEN) > 0 &&
         dcode25->character > CFG(*dcode25, ZBAR_CFG_MAX_LEN))) {
-        dprintf(2, " [invalid len]\n");
+        zbar_dprintf(2, " [invalid len]\n");
         dcode->lock = 0;
         dcode25->character = -1;
         return(ZBAR_NONE);
@@ -168,7 +168,7 @@ static inline signed char i25_decode_end
 
     dcode->buflen = dcode25->character;
     dcode->buf[dcode25->character] = '\0';
-    dprintf(2, " [valid end]\n");
+    zbar_dprintf(2, " [valid end]\n");
     dcode25->character = -1;
     return(ZBAR_I25);
 }
@@ -193,24 +193,24 @@ zbar_symbol_type_t _zbar_decode_i25 (zba
     /* FIXME check current character width against previous */
     dcode25->width = dcode25->s10;
 
-    dprintf(2, "      i25[%c%02d+%x]",
+    zbar_dprintf(2, "      i25[%c%02d+%x]",
             (dcode25->direction) ? '<' : '>',
             dcode25->character, dcode25->element);
 
     /* lock shared resources */
     if(!dcode25->character && get_lock(dcode, ZBAR_I25)) {
         dcode25->character = -1;
-        dprintf(2, " [locked %d]\n", dcode->lock);
+        zbar_dprintf(2, " [locked %d]\n", dcode->lock);
         return(ZBAR_PARTIAL);
     }
 
     unsigned char c = i25_decode10(dcode, 1);
-    dprintf(2, " c=%x", c);
+    zbar_dprintf(2, " c=%x", c);
 
     if(c > 9 ||
        ((dcode25->character >= BUFFER_MIN) &&
         size_buf(dcode, dcode25->character + 2))) {
-        dprintf(2, (c > 9) ? " [aborted]\n" : " [overflow]\n");
+        zbar_dprintf(2, (c > 9) ? " [aborted]\n" : " [overflow]\n");
         dcode->lock = 0;
         dcode25->character = -1;
         return(ZBAR_NONE);
@@ -218,15 +218,15 @@ zbar_symbol_type_t _zbar_decode_i25 (zba
     dcode->buf[dcode25->character++] = c + '0';
 
     c = i25_decode10(dcode, 0);
-    dprintf(2, " c=%x", c);
+    zbar_dprintf(2, " c=%x", c);
     if(c > 9) {
-        dprintf(2, " [aborted]\n");
+        zbar_dprintf(2, " [aborted]\n");
         dcode->lock = 0;
         dcode25->character = -1;
         return(ZBAR_NONE);
     }
     else
-        dprintf(2, "\n");
+        zbar_dprintf(2, "\n");
 
     dcode->buf[dcode25->character++] = c + '0';
     dcode25->element = 10;
