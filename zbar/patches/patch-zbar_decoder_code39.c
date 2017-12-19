$NetBSD$

--- zbar/decoder/code39.c.orig	2009-10-23 18:16:44.000000000 +0000
+++ zbar/decoder/code39.c
@@ -136,10 +136,10 @@ static inline unsigned char code39_decod
     enc <<= 1;
     if(E > 2) {
         enc |= 1;
-        dprintf(2, "1");
+        zbar_dprintf(2, "1");
     }
     else
-        dprintf(2, "0");
+        zbar_dprintf(2, "0");
     return(enc);
 }
 
@@ -147,7 +147,7 @@ static inline signed char code39_decode9
 {
     code39_decoder_t *dcode39 = &dcode->code39;
 
-    dprintf(2, " s=%d ", dcode39->s9);
+    zbar_dprintf(2, " s=%d ", dcode39->s9);
     if(dcode39->s9 < 9)
         return(-1);
 
@@ -181,7 +181,7 @@ static inline signed char code39_decode9
     zassert(idx < 0x2c, -1, " idx=%x enc=%x s9=%x\n", idx, enc, dcode39->s9);
 
     const char39_t *c = &code39_encodings[idx];
-    dprintf(2, " i=%02x chk=%02x c=%02x/%02x", idx, c->chk, c->fwd, c->rev);
+    zbar_dprintf(2, " i=%02x chk=%02x c=%02x/%02x", idx, c->chk, c->fwd, c->rev);
     if(enc != c->chk)
         return(-1);
 
@@ -197,20 +197,20 @@ static inline signed char code39_decode_
     if(c == 0x19)
         dcode39->direction ^= 1;
     else if(c != 0x2b) {
-        dprintf(2, "\n");
+        zbar_dprintf(2, "\n");
         return(ZBAR_NONE);
     }
 
     /* check leading quiet zone - spec is 10x */
     unsigned quiet = get_width(dcode, 9);
     if(quiet && quiet < dcode39->s9 / 2) {
-        dprintf(2, " [invalid quiet]\n");
+        zbar_dprintf(2, " [invalid quiet]\n");
         return(ZBAR_NONE);
     }
 
     dcode39->element = 9;
     dcode39->character = 0;
-    dprintf(1, " dir=%x [valid start]\n", dcode39->direction);
+    zbar_dprintf(1, " dir=%x [valid start]\n", dcode39->direction);
     return(ZBAR_PARTIAL);
 }
 
@@ -220,7 +220,7 @@ static inline void code39_postprocess (z
     int i;
     if(dcode39->direction) {
         /* reverse buffer */
-        dprintf(2, " (rev)");
+        zbar_dprintf(2, " (rev)");
         for(i = 0; i < dcode39->character / 2; i++) {
             unsigned j = dcode39->character - 1 - i;
             char code = dcode->buf[i];
@@ -247,14 +247,14 @@ zbar_symbol_type_t _zbar_decode_code39 (
     if(dcode39->character < 0) {
         if(get_color(dcode) != ZBAR_BAR)
             return(ZBAR_NONE);
-        dprintf(2, "      code39:");
+        zbar_dprintf(2, "      code39:");
         return(code39_decode_start(dcode));
     }
 
     if(++dcode39->element < 9)
         return(ZBAR_NONE);
 
-    dprintf(2, "      code39[%c%02d+%x]",
+    zbar_dprintf(2, "      code39[%c%02d+%x]",
             (dcode39->direction) ? '<' : '>',
             dcode39->character, dcode39->element);
 
@@ -268,19 +268,19 @@ zbar_symbol_type_t _zbar_decode_code39 (
 
             /* trailing quiet zone check */
             if(space && space < dcode39->width / 2) {
-                dprintf(2, " [invalid qz]\n");
+                zbar_dprintf(2, " [invalid qz]\n");
                 sym = ZBAR_NONE;
             }
             else if(dcode39->character < CFG(*dcode39, ZBAR_CFG_MIN_LEN) ||
                     (CFG(*dcode39, ZBAR_CFG_MAX_LEN) > 0 &&
                      dcode39->character > CFG(*dcode39, ZBAR_CFG_MAX_LEN))) {
-                dprintf(2, " [invalid len]\n");
+                zbar_dprintf(2, " [invalid len]\n");
                 sym = ZBAR_NONE;
             }
             else {
                 /* FIXME checksum (needs config enable) */
                 code39_postprocess(dcode);
-                dprintf(2, " [valid end]\n");
+                zbar_dprintf(2, " [valid end]\n");
             }
             dcode39->character = -1;
             if(!sym)
@@ -291,34 +291,34 @@ zbar_symbol_type_t _zbar_decode_code39 (
             /* inter-character space check failure */
             dcode->lock = 0;
             dcode39->character = -1;
-            dprintf(2, " ics>%d [invalid ics]", dcode39->width);
+            zbar_dprintf(2, " ics>%d [invalid ics]", dcode39->width);
         }
         dcode39->element = 0;
-        dprintf(2, "\n");
+        zbar_dprintf(2, "\n");
         return(ZBAR_NONE);
     }
 
     signed char c = code39_decode9(dcode);
-    dprintf(2, " c=%d", c);
+    zbar_dprintf(2, " c=%d", c);
 
     /* lock shared resources */
     if(!dcode39->character && get_lock(dcode, ZBAR_CODE39)) {
         dcode39->character = -1;
-        dprintf(1, " [locked %d]\n", dcode->lock);
+        zbar_dprintf(1, " [locked %d]\n", dcode->lock);
         return(ZBAR_PARTIAL);
     }
 
     if(c < 0 ||
        ((dcode39->character >= BUFFER_MIN) &&
         size_buf(dcode, dcode39->character + 1))) {
-        dprintf(1, (c < 0) ? " [aborted]\n" : " [overflow]\n");
+        zbar_dprintf(1, (c < 0) ? " [aborted]\n" : " [overflow]\n");
         dcode->lock = 0;
         dcode39->character = -1;
         return(ZBAR_NONE);
     }
     else {
         zassert(c < 0x2c, ZBAR_NONE, "c=%02x s9=%x\n", c, dcode39->s9);
-        dprintf(2, "\n");
+        zbar_dprintf(2, "\n");
     }
 
     dcode->buf[dcode39->character++] = c;
