$NetBSD$

--- aclocal.m4.orig	2015-12-01 13:36:25.000000000 +0000
+++ aclocal.m4
@@ -4597,7 +4597,7 @@ freebsd* | dragonfly*)
     objformat=`/usr/bin/objformat`
   else
     case $host_os in
-    freebsd[[123]].*) objformat=aout ;;
+    freebsd[[123]]|freebsd[[123]].*) objformat=aout ;;
     *) objformat=elf ;;
     esac
   fi
@@ -6214,7 +6214,7 @@ case $host_os in
 	;;
     esac
     ;;
-  freebsd[[12]].*)
+  freebsd[[12]]|freebsd[[12]].*)
     # C++ shared libraries reported to be fairly broken before switch to ELF
     _LT_AC_TAGVAR(ld_shlibs, $1)=no
     ;;
