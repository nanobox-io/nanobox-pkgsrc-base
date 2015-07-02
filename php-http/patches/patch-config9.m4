$NetBSD$

--- config9.m4.orig	2014-04-24 12:35:48.000000000 +0000
+++ config9.m4
@@ -109,7 +109,7 @@ dnl ZLIB
 dnl ----
 	AC_MSG_CHECKING([for zlib.h])
 	ZLIB_DIR=
-	for i in "$PHP_HTTP_ZLIB_DIR" "$PHP_ZLIB_DIR" "$PHP_ZLIB" /usr/local /usr /opt; do
+	for i in "$PHP_HTTP_ZLIB_DIR" "$PHP_ZLIB_DIR" "$PHP_ZLIB" /usr/local /usr /opt/local /opt; do
 		if test -f "$i/include/zlib.h"; then
 			ZLIB_DIR=$i
 			break;
@@ -140,7 +140,7 @@ dnl ----
 	else
 		AC_MSG_CHECKING([for curl/curl.h])
 		CURL_DIR=
-		for i in "$PHP_HTTP_LIBCURL_DIR" /usr/local /usr /opt; do
+		for i in "$PHP_HTTP_LIBCURL_DIR" /usr/local /usr /opt/local /opt; do
 			if test -f "$i/include/curl/curl.h"; then
 				CURL_DIR=$i
 				break
@@ -290,7 +290,7 @@ dnl ----
 	else
 		AC_MSG_CHECKING([for event2/event.h])
 		EVENT_DIR=
-		for i in "$PHP_HTTP_LIBEVENT_DIR" /usr/local /usr /opt; do
+		for i in "$PHP_HTTP_LIBEVENT_DIR" /usr/local /usr /opt/local /opt; do
 			if test -f "$i/include/event.h"; then
 				EVENT_DIR=$i
 				break
