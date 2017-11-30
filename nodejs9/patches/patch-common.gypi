$NetBSD$

--- common.gypi.orig	2017-11-14 20:57:59.000000000 +0000
+++ common.gypi
@@ -291,7 +291,7 @@
         'cflags': [ '-pthread', ],
         'ldflags': [ '-pthread' ],
       }],
-      [ 'OS in "linux freebsd openbsd solaris android aix cloudabi"', {
+      [ 'OS in "linux freebsd openbsd solaris android aix netbsd cloudabi"', {
         'cflags': [ '-Wall', '-Wextra', '-Wno-unused-parameter', ],
         'cflags_cc': [ '-fno-rtti', '-fno-exceptions', '-std=gnu++0x' ],
         'ldflags': [ '-rdynamic' ],
