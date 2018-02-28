$NetBSD$

--- src/timezone/strftime.c.orig	2017-11-06 22:13:17.000000000 +0000
+++ src/timezone/strftime.c
@@ -112,7 +112,7 @@ enum warn
 };
 
 static char *_add(const char *, char *, const char *);
-static char *_conv(int, const char *, char *, const char *);
+static char *_conv(const int, const char *, char *, const char *);
 static char *_fmt(const char *, const struct pg_tm *, char *, const char *,
 	 enum warn *);
 static char *_yconv(int, int, bool, bool, char *, const char *);
