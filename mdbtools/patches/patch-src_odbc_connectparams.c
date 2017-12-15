$NetBSD$

--- src/odbc/connectparams.c.orig	2004-05-30 08:06:43.000000000 +0000
+++ src/odbc/connectparams.c
@@ -21,7 +21,9 @@
 
 #include <stdlib.h>
 #include <stdio.h>
+#include <ctype.h>
 #include <string.h>
+#include <odbcinst.h>
 #include <sys/stat.h>
 
 #include "connectparams.h"
