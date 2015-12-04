$NetBSD$

--- build/libtool.m4.orig	2015-11-25 20:28:38.000000000 +0000
+++ build/libtool.m4
@@ -1545,7 +1545,7 @@ freebsd* | dragonfly*)
     objformat=`/usr/bin/objformat`
   else
     case $host_os in
-    freebsd[[123]].*) objformat=aout ;;
+    freebsd[[123]]|freebsd[[123]].*) objformat=aout ;;
     *) objformat=elf ;;
     esac
   fi
@@ -3162,7 +3162,7 @@ case $host_os in
 	;;
     esac
     ;;
-  freebsd[[12]].*)
+  reebsd[[12]]|freebsd[[12]].*)
     # C++ shared libraries reported to be fairly broken before switch to ELF
     _LT_AC_TAGVAR(ld_shlibs, $1)=no
     ;;
