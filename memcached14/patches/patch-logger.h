$NetBSD$

--- logger.h.orig	2017-01-08 01:10:24.000000000 +0000
+++ logger.h
@@ -11,7 +11,7 @@
 #define GET_LOGGER() ((logger *) pthread_getspecific(logger_key));
 
 /* Inlined from memcached.h - should go into sub header */
-typedef unsigned int rel_time_t;
+typedef intmax_t rel_time_t;
 
 enum log_entry_type {
     LOGGER_ASCII_CMD = 0,
