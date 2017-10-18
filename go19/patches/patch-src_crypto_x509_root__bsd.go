$NetBSD$

--- src/crypto/x509/root_bsd.go.orig	2017-08-24 21:50:31.000000000 +0000
+++ src/crypto/x509/root_bsd.go
@@ -12,4 +12,5 @@ var certFiles = []string{
 	"/etc/ssl/cert.pem",                      // OpenBSD
 	"/usr/local/share/certs/ca-root-nss.crt", // DragonFly
 	"/etc/openssl/certs/ca-certificates.crt", // NetBSD
+	"/etc/ssl/certs/ca-certificates.crt",     // NetBSD
 }
