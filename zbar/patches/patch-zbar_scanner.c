$NetBSD$

--- zbar/scanner.c.orig	2009-10-23 18:16:44.000000000 +0000
+++ zbar/scanner.c
@@ -127,7 +127,7 @@ static inline unsigned calc_thresh (zbar
     /* threshold 1st to improve noise rejection */
     unsigned thresh = scn->y1_thresh;
     if((thresh <= scn->y1_min_thresh) || !scn->width) {
-        dprintf(1, " tmin=%d", scn->y1_min_thresh);
+        zbar_dprintf(1, " tmin=%d", scn->y1_min_thresh);
         return(scn->y1_min_thresh);
     }
     /* slowly return threshold to min */
@@ -135,7 +135,7 @@ static inline unsigned calc_thresh (zbar
     unsigned long t = thresh * dx;
     t /= scn->width;
     t /= ZBAR_SCANNER_THRESH_FADE;
-    dprintf(1, " thr=%d t=%ld x=%d last=%d.%d (%d)",
+    zbar_dprintf(1, " thr=%d t=%ld x=%d last=%d.%d (%d)",
             thresh, t, scn->x, scn->last_edge >> ZBAR_FIXED,
             scn->last_edge & ((1 << ZBAR_FIXED) - 1), dx);
     if(thresh > t) {
@@ -156,7 +156,7 @@ static inline zbar_symbol_type_t process
         scn->last_edge = scn->cur_edge;
 
     scn->width = scn->cur_edge - scn->last_edge;
-    dprintf(1, " sgn=%d cur=%d.%d w=%d (%s)\n",
+    zbar_dprintf(1, " sgn=%d cur=%d.%d w=%d (%s)\n",
             scn->y1_sign, scn->cur_edge >> ZBAR_FIXED,
             scn->cur_edge & ((1 << ZBAR_FIXED) - 1), scn->width,
             ((y1 > 0) ? "SPACE" : "BAR"));
@@ -180,7 +180,7 @@ inline zbar_symbol_type_t zbar_scanner_f
     unsigned x = (scn->x << ZBAR_FIXED) + ROUND;
 
     if(scn->cur_edge != x || scn->y1_sign > 0) {
-        dprintf(1, "flush0:");
+        zbar_dprintf(1, "flush0:");
         zbar_symbol_type_t edge = process_edge(scn, -scn->y1_sign);
         scn->cur_edge = x;
         scn->y1_sign = -scn->y1_sign;
@@ -240,7 +240,7 @@ zbar_symbol_type_t zbar_scan_y (zbar_sca
     register int y2_1 = y0_0 - (y0_1 * 2) + y0_2;
     register int y2_2 = y0_1 - (y0_2 * 2) + y0_3;
 
-    dprintf(1, "scan: x=%d y=%d y0=%d y1=%d y2=%d",
+    zbar_dprintf(1, "scan: x=%d y=%d y0=%d y1=%d y2=%d",
             x, y, y0_1, y1_1, y2_1);
 
     zbar_symbol_type_t edge = ZBAR_NONE;
@@ -261,7 +261,7 @@ zbar_symbol_type_t zbar_scan_y (zbar_sca
             /* adaptive thresholding */
             /* start at multiple of new min/max */
             scn->y1_thresh = (abs(y1_1) * THRESH_INIT + ROUND) >> ZBAR_FIXED;
-            dprintf(1, "\tthr=%d", scn->y1_thresh);
+            zbar_dprintf(1, "\tthr=%d", scn->y1_thresh);
             if(scn->y1_thresh < scn->y1_min_thresh)
                 scn->y1_thresh = scn->y1_min_thresh;
 
@@ -274,11 +274,11 @@ zbar_symbol_type_t zbar_scan_y (zbar_sca
                 /* interpolate zero crossing */
                 scn->cur_edge -= ((y2_1 << ZBAR_FIXED) + 1) / d;
             scn->cur_edge += x << ZBAR_FIXED;
-            dprintf(1, "\n");
+            zbar_dprintf(1, "\n");
         }
     }
     else
-        dprintf(1, "\n");
+        zbar_dprintf(1, "\n");
     /* FIXME add fall-thru pass to decoder after heuristic "idle" period
        (eg, 6-8 * last width) */
     scn->x = x + 1;
@@ -307,5 +307,5 @@ void zbar_scanner_get_state (const zbar_
     /* NB not quite accurate (uses updated x) */
     zbar_scanner_t *mut_scn = (zbar_scanner_t*)scn;
     if(y1_thresh) *y1_thresh = calc_thresh(mut_scn);
-    dprintf(1, "\n");
+    zbar_dprintf(1, "\n");
 }
