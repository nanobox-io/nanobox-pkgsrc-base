$NetBSD$

--- config9.m4.orig	2016-12-12 09:04:21.000000000 +0000
+++ config9.m4
@@ -26,13 +26,13 @@ if test "$PHP_HTTP" != "no"; then
 
 	dnl ZLIB
 	PHP_ARG_WITH([http-zlib-dir], [whether/where to check for zlib],
-	[  --with-http-zlib-dir[=DIR]         HTTP: where to find zlib], $PHP_HTTP, no)
+	[  --with-http-zlib-dir[=DIR]         HTTP: where to find zlib], $PHP_HTTP_ZLIB_DIR, no)
 	PECL_CHECK_ZLIB([$PHP_HTTP_ZLIB_DIR], [1.2.0.4])
 	PECL_CHECK_DONE(zlib, $PECL_VAR([HAVE_ZLIB]))
 
 	dnl CURL
 	PHP_ARG_WITH([http-libcurl-dir], [whether/where to check for libcurl],
-	[  --with-http-libcurl-dir[=DIR]      HTTP: where to find libcurl], $PHP_HTTP, no)
+	[  --with-http-libcurl-dir[=DIR]      HTTP: where to find libcurl], $PHP_HTTP_LIBCURL_DIR, no)
 	if test "$PHP_HTTP_LIBCURL_DIR" != "no"; then
 		PECL_CHECK_LIBCURL([$PHP_HTTP_LIBCURL_DIR], [7.18.2])
 		PECL_HAVE_LIBCURL_PROTOCOL([HTTP], [
@@ -47,7 +47,7 @@ if test "$PHP_HTTP" != "no"; then
 
 	dnl EVENT
 	PHP_ARG_WITH([http-libevent-dir], [whether/where to check for libevent],
-	[  --with-http-libevent-dir[=DIR]     HTTP: where to find libevent], $PHP_HTTP_LIBCURL_DIR, no)
+	[  --with-http-libevent-dir[=DIR]     HTTP: where to find libevent], $PHP_HTTP_LIBEVENT_DIR, no)
 	if test "$PHP_HTTP_LIBEVENT_DIR" != "no"; then
 		PECL_CHECK_LIBEVENT([$PHP_HTTP_LIBEVENT_DIR])
 		PECL_CHECK_DONE(libevent, [$PECL_VAR([HAVE_LIBEVENT])])
@@ -55,7 +55,7 @@ if test "$PHP_HTTP" != "no"; then
 
 	dnl GNU IDNA
 	PHP_ARG_WITH([http-libidn2-dir], [whether/where to check for libidn2],
-	[  --with-http-libidn2-dir[=DIR]      HTTP: where to find libidn2], $PHP_HTTP_LIBCURL_DIR, no)
+	[  --with-http-libidn2-dir[=DIR]      HTTP: where to find libidn2], $PHP_HTTP_LIBIDN2_DIR, no)
 	if test "$PHP_HTTP_LIBIDN2_DIR" != "no"; then
 		PECL_CHECK_CUSTOM(libidn2, "$PHP_HTTP_LIBIDN2_DIR", idn2.h, idn2,
 			[$($EGREP "define IDN2_VERSION " "include/idn2.h" | $SED -e's/^.*VERSION //g' -e 's/@<:@^0-9\.@:>@//g')])
@@ -65,7 +65,7 @@ if test "$PHP_HTTP" != "no"; then
 		PECL_CHECK_DONE(libidn2, $PECL_VAR([HAVE_LIBIDN2]))
 	fi
 	PHP_ARG_WITH([http-libidn-dir], [whether/where to check for libidn],
-	[  --with-http-libidn-dir[=DIR]       HTTP: where to find libidn], $PHP_HTTP_LIBCURL_DIR, no)
+	[  --with-http-libidn-dir[=DIR]       HTTP: where to find libidn], $PHP_HTTP_LIBIDN_DIR, no)
 	if test "$PHP_HTTP_LIBIDN_DIR" != "no"; then
 		PECL_CHECK_PKGCONFIG(libidn, [$PHP_HTTP_LIBIDN_DIR])
 		if $PECL_VAR([HAVE_LIBIDN]); then
@@ -117,7 +117,7 @@ if test "$PHP_HTTP" != "no"; then
 
 	dnl IDNKIT2
 	PHP_ARG_WITH([http-libidnkit2-dir], [whether/where to check for libidnkit2],
-	[  --with-http-libidnkit2-dir[=DIR]   HTTP: where to find libidnkit2], $PHP_HTTP_LIBCURL_DIR, no)
+	[  --with-http-libidnkit2-dir[=DIR]   HTTP: where to find libidnkit2], $PHP_HTTP_LIBIDNKIT2_DIR, no)
 	if test "$PHP_HTTP_LIBIDNKIT2_DIR" != "no"; then
 		PECL_CHECK_CUSTOM(libidnkit2, "$PHP_HTTP_LIBIDNKIT2_DIR", idn/api.h, idnkit,
 			[$($EGREP "define IDNKIT_VERSION_LIBIDN\b" "include/idn/version.h" | $SED -e's/^.*VERSION_LIBIDN//g' -e 's/@<:@^0-9\.@:>@//g')])
@@ -128,7 +128,7 @@ if test "$PHP_HTTP" != "no"; then
 	fi
 	dnl IDNKIT1
 	PHP_ARG_WITH([http-libidnkit-dir], [whether/where to check for libidnkit],
-	[  --with-http-libidnkit-dir[=DIR]    HTTP: where to find libidnkit], $PHP_HTTP_LIBCURL_DIR, no)
+	[  --with-http-libidnkit-dir[=DIR]    HTTP: where to find libidnkit], $PHP_HTTP_LIBIDNKIT_DIR, no)
 	if test "$PHP_HTTP_LIBIDNKIT_DIR" != "no"; then
 		# libidnkit1 and libidnkit2 have the same API
 		if test "$PHP_HTTP_LIBIDNKIT2_DIR" != no && $PECL_VAR([HAVE_LIBIDNKIT2]); then
