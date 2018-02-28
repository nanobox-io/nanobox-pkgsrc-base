$NetBSD$

--- src/mongo/platform/random.cpp.orig	2018-01-04 23:28:55.000000000 +0000
+++ src/mongo/platform/random.cpp
@@ -147,7 +147,7 @@ std::unique_ptr<SecureRandom> SecureRand
     return stdx::make_unique<WinSecureRandom>();
 }
 
-#elif defined(__linux__) || defined(__sun) || defined(__APPLE__) || defined(__FreeBSD__)
+#elif defined(__linux__) || defined(__sun) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__)
 
 class InputStreamSecureRandom : public SecureRandom {
 public:
