$NetBSD$

--- deps/uv/common.gypi.orig	2015-09-08 15:30:37.000000000 +0000
+++ deps/uv/common.gypi
@@ -129,7 +129,7 @@
           }]
         ]
       }],
-      ['OS in "freebsd linux openbsd solaris android"', {
+      ['OS in "freebsd dragonflybsd linux openbsd solaris android netbsd"', {
         'cflags': [ '-Wall' ],
         'cflags_cc': [ '-fno-rtti', '-fno-exceptions' ],
         'target_conditions': [
