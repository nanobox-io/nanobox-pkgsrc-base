$NetBSD$

--- fh_cache.c.orig	2007-01-05 15:08:12.000000000 +0000
+++ fh_cache.c
@@ -180,6 +180,13 @@ static char *fh_cache_lookup(uint32 dev,
 	    /* cache hit, update time on cache entry */
 	    fh_cache[i].use = fh_cache_next();
 
+            if (buf.st_mtime < 0)
+                buf.st_mtime = st_cache.st_mtime;
+            if (buf.st_atime < 0)
+                buf.st_atime = st_cache.st_atime;
+            if (buf.st_ctime < 0)
+                buf.st_ctime = st_cache.st_ctime;
+
 	    /* update stat cache */
 	    st_cache_valid = TRUE;
 	    st_cache = buf;
