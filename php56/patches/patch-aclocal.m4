$NetBSD$

--- aclocal.m4.orig	2015-11-25 23:43:22.000000000 +0000
+++ aclocal.m4
@@ -4578,7 +4578,7 @@ freebsd* | dragonfly*)
     objformat=`/usr/bin/objformat`
   else
     case $host_os in
-    freebsd[[123]].*) objformat=aout ;;
+    freebsd[[123]]|freebsd[[123]].*) objformat=aout ;;
     *) objformat=elf ;;
     esac
   fi
@@ -6195,7 +6195,7 @@ case $host_os in
 	;;
     esac
     ;;
-  freebsd[[12]].*)
+  freebsd[[12]]|freebsd[[12]].*)
     # C++ shared libraries reported to be fairly broken before switch to ELF
     _LT_AC_TAGVAR(ld_shlibs, $1)=no
     ;;
