$NetBSD$

--- zbar/decoder/qr_finder.c.orig	2009-10-23 18:16:44.000000000 +0000
+++ zbar/decoder/qr_finder.c
@@ -29,25 +29,25 @@ zbar_symbol_type_t _zbar_find_qr (zbar_d
     if(get_color(dcode) != ZBAR_SPACE || s < 7)
         return(0);
 
-    dprintf(2, "    qrf: s=%d", s);
+    zbar_dprintf(2, "    qrf: s=%d", s);
 
     int ei = decode_e(pair_width(dcode, 1), s, 7);
-    dprintf(2, " %d", ei);
+    zbar_dprintf(2, " %d", ei);
     if(ei)
         goto invalid;
 
     ei = decode_e(pair_width(dcode, 2), s, 7);
-    dprintf(2, "%d", ei);
+    zbar_dprintf(2, "%d", ei);
     if(ei != 2)
         goto invalid;
 
     ei = decode_e(pair_width(dcode, 3), s, 7);
-    dprintf(2, "%d", ei);
+    zbar_dprintf(2, "%d", ei);
     if(ei != 2)
         goto invalid;
 
     ei = decode_e(pair_width(dcode, 4), s, 7);
-    dprintf(2, "%d", ei);
+    zbar_dprintf(2, "%d", ei);
     if(ei)
         goto invalid;
 
@@ -63,13 +63,13 @@ zbar_symbol_type_t _zbar_find_qr (zbar_d
     w = get_width(dcode, 5);
     qrf->line.boffs = qrf->line.pos[0] + get_width(dcode, 4) + (w + 1) / 2;
 
-    dprintf(2, " boff=%d pos=%d len=%d eoff=%d [valid]\n",
+    zbar_dprintf(2, " boff=%d pos=%d len=%d eoff=%d [valid]\n",
             qrf->line.boffs, qrf->line.pos[0], qrf->line.len,
             qrf->line.eoffs);
 
     return(ZBAR_QRCODE);
 
 invalid:
-    dprintf(2, " [invalid]\n");
+    zbar_dprintf(2, " [invalid]\n");
     return(0);
 }
