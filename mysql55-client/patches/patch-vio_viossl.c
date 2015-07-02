$NetBSD$

--- vio/viossl.c.orig	2014-06-09 16:47:09.998330571 +0000
+++ vio/viossl.c
@@ -171,10 +171,8 @@ static int ssl_do(struct st_VioSSLFd *pt
   SSL_clear(ssl);
   SSL_SESSION_set_timeout(SSL_get_session(ssl), timeout);
   SSL_set_fd(ssl, vio->sd);
-#ifndef HAVE_YASSL
-# if defined SSL_OP_NO_COMPRESSION
+#if !defined(HAVE_YASSL) && defined(SSL_OP_NO_COMPRESSION)
   SSL_set_options(ssl, SSL_OP_NO_COMPRESSION);
-# endif
 #endif
 
   if ((r= connect_accept_func(ssl)) < 1)
