$NetBSD$

--- zbar/decoder/pdf417.c.orig	2009-10-23 18:16:44.000000000 +0000
+++ zbar/decoder/pdf417.c
@@ -41,7 +41,7 @@ static inline signed short pdf417_decode
      * from similar edge measurements
      */
     unsigned s = dcode->pdf417.s8;
-    dprintf(2, " s=%d ", s);
+    zbar_dprintf(2, " s=%d ", s);
     if(s < 8)
         return(-1);
 
@@ -55,19 +55,19 @@ static inline signed short pdf417_decode
         else
             e = decode_e(get_width(dcode, 7 - i) +
                          get_width(dcode, 6 - i), s, 17);
-        dprintf(4, "%x", e);
+        zbar_dprintf(4, "%x", e);
         if(e < 0 || e > 8)
             return(-1);
         sig = (sig << 3) ^ e;
     }
-    dprintf(2, " sig=%06lx", sig);
+    zbar_dprintf(2, " sig=%06lx", sig);
 
     /* determine cluster number */
     int clst = ((sig & 7) - ((sig >> 3) & 7) +
                 ((sig >> 12) & 7) - ((sig >> 15) & 7));
     if(clst < 0)
         clst += 9;
-    dprintf(2, " k=%d", clst);
+    zbar_dprintf(2, " k=%d", clst);
     zassert(clst >= 0 && clst < 9, -1, "dir=%x sig=%lx k=%x %s\n",
             dcode->pdf417.direction, sig, clst,
             _zbar_decoder_buf_dump(dcode->buf, dcode->pdf417.character));
@@ -89,7 +89,7 @@ static inline signed short pdf417_decode
             _zbar_decoder_buf_dump(dcode->buf, dcode->pdf417.character));
 
     unsigned short c = (g[0] + g[1] + g[2]) & PDF417_HASH_MASK;
-    dprintf(2, " g0=%x g1=%x g2=%x c=%03d(%d)",
+    zbar_dprintf(2, " g0=%x g1=%x g2=%x c=%03d(%d)",
             g[0], g[1], g[2], c & 0x3ff, c >> 10);
     return(c);
 }
@@ -142,18 +142,18 @@ static inline signed char pdf417_decode_
         ei = decode_e(get_width(dcode, 8) + get_width(dcode, 9), s, 17);
     }
 
-    dprintf(2, "      pdf417[%c]: s=%d",
+    zbar_dprintf(2, "      pdf417[%c]: s=%d",
             (get_color(dcode)) ? '<' : '>', s);
 
     /* check quiet zone */
     if(ei >= 0 && ei < ex) {
-        dprintf(2, " [invalid quiet]\n");
+        zbar_dprintf(2, " [invalid quiet]\n");
         return(0);
     }
 
     /* lock shared resources */
     if(get_lock(dcode, ZBAR_PDF417)) {
-        dprintf(2, " [locked %d]\n", dcode->lock);
+        zbar_dprintf(2, " [locked %d]\n", dcode->lock);
         return(0);
     }
 
@@ -162,7 +162,7 @@ static inline signed char pdf417_decode_
     dcode417->element = 0;
     dcode417->character = 0;
 
-    dprintf(2, " [valid start]\n");
+    zbar_dprintf(2, " [valid start]\n");
     return(ZBAR_PARTIAL);
 }
 
@@ -176,7 +176,7 @@ zbar_symbol_type_t _zbar_decode_pdf417 (
 
     if(dcode417->character < 0) {
         pdf417_decode_start(dcode);
-        dprintf(4, "\n");
+        zbar_dprintf(4, "\n");
         return(0);
     }
 
@@ -185,7 +185,7 @@ zbar_symbol_type_t _zbar_decode_pdf417 (
         return(0);
     dcode417->element = 0;
 
-    dprintf(2, "      pdf417[%c%02d]:",
+    zbar_dprintf(2, "      pdf417[%c%02d]:",
             (dcode417->direction) ? '<' : '>', dcode417->character);
 
     if(get_color(dcode) != dcode417->direction) {
@@ -202,7 +202,7 @@ zbar_symbol_type_t _zbar_decode_pdf417 (
     if((c < 0) ||
        ((dcode417->character >= BUFFER_MIN) &&
         size_buf(dcode, dcode417->character + 1))) {
-        dprintf(1, (c < 0) ? " [aborted]\n" : " [overflow]\n");
+        zbar_dprintf(1, (c < 0) ? " [aborted]\n" : " [overflow]\n");
         dcode->lock = 0;
         dcode417->character = -1;
         return(0);
@@ -211,12 +211,12 @@ zbar_symbol_type_t _zbar_decode_pdf417 (
     /* FIXME TBD infer dimensions, save codewords */
 
     if(c == PDF417_STOP) {
-        dprintf(1, " [valid stop]");
+        zbar_dprintf(1, " [valid stop]");
         /* FIXME check trailing bar and qz */
         dcode->lock = 0;
         dcode417->character = -1;
     }
 
-    dprintf(2, "\n");
+    zbar_dprintf(2, "\n");
     return(0);
 }
