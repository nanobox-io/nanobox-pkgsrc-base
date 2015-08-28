$NetBSD$

--- third-party/folly/src/folly/io/async/AsyncSSLSocket.cpp.orig	2015-08-25 22:48:36.000000000 +0000
+++ third-party/folly/src/folly/io/async/AsyncSSLSocket.cpp
@@ -325,7 +325,8 @@ AsyncSSLSocket::~AsyncSSLSocket() {
 void AsyncSSLSocket::init() {
   // Do this here to ensure we initialize this once before any use of
   // AsyncSSLSocket instances and not as part of library load.
-  static const auto eorAwareBioMethodInitializer = initEorBioMethod();
+  //static const auto eorAwareBioMethodInitializer = initEorBioMethod();
+  (void)initEorBioMethod();
   setup_SSL_CTX(ctx_->getSSLCtx());
 }
 
