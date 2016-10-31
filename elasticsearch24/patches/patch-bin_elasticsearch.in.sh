$NetBSD$

--- bin/elasticsearch.in.sh.orig	2016-08-23 16:46:25.000000000 +0000
+++ bin/elasticsearch.in.sh
@@ -10,7 +10,7 @@ EOF
     exit 1
 fi
 
-ES_CLASSPATH="$ES_HOME/lib/elasticsearch-2.4.1.jar:$ES_HOME/lib/*"
+ES_CLASSPATH="@ES_LIBDIR@/elasticsearch-2.4.0.jar:@ES_LIBDIR@/*"
 
 if [ "x$ES_MIN_MEM" = "x" ]; then
     ES_MIN_MEM=256m
