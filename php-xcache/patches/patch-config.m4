$NetBSD$

--- config.m4.orig	2013-06-18 02:45:50.000000000 +0000
+++ config.m4
@@ -96,7 +96,7 @@ done
     fi
   fi
   PHP_SUBST([XCACHE_AWK])
-  AC_PATH_PROGS([M4], [m4])
+  AC_PATH_PROGS([M4], [gm4 m4])
   if test "$PHP_XCACHE_TEST" != "no"; then
     if echo | "$M4" -E > /dev/null 2>&1 ; then
       M4="$M4 -E"
