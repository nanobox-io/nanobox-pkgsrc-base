$NetBSD$

--- src/mongo/platform/random.cpp.orig	2015-10-12 20:46:18.000000000 +0000
+++ src/mongo/platform/random.cpp
@@ -106,7 +106,7 @@ SecureRandom* SecureRandom::create() {
     return new WinSecureRandom();
 }
 
-#elif defined(__linux__) || defined(__sunos__) || defined(__APPLE__) || defined(__freebsd__)
+#elif defined(__linux__) || defined(__sunos__) || defined(__APPLE__) || defined(__freebsd__) || defined(__netbsd__)
 
 class InputStreamSecureRandom : public SecureRandom {
 public:
