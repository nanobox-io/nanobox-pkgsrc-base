$NetBSD$

--- aclocal.m4.orig	2008-12-31 15:52:09.000000000 +0000
+++ aclocal.m4
@@ -3,7 +3,7 @@ dnl
 AC_DEFUN([UNFS3_SOLARIS_RPC],[
   AC_CHECK_FUNC(svc_tli_create, [
     # On Solaris, you must link with librpcsoc, or the binaries won't work. 
-    LDFLAGS="-L/usr/ucblib -R/usr/ucblib $LDFLAGS"
+    LDFLAGS="-L/usr/ucblib/amd64 -R/usr/ucblib/amd64 $LDFLAGS"
     AC_CHECK_LIB(rpcsoc, svctcp_create, 
         [ LIBS="-lrpcsoc $LIBS" ],
         [ AC_MSG_WARN([*** Cannot find librpcsoc. On Solaris, install package SUNWscpu. ***]) ]
