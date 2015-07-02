$NetBSD$

--- config.m4.orig	2013-03-14 17:07:03.000000000 +0000
+++ config.m4
@@ -42,13 +42,13 @@ if test "$PHP_SNMP" != "no"; then
     dnl
 
     if test "$PHP_SNMP" = "yes"; then
-      for i in /usr/include /usr/local/include; do
+      for i in /usr/include /usr/local/include /opt/local/include; do
         test -f $i/snmp.h                       && SNMP_INCDIR=$i
         test -f $i/ucd-snmp/snmp.h              && SNMP_INCDIR=$i/ucd-snmp
         test -f $i/snmp/snmp.h                  && SNMP_INCDIR=$i/snmp
         test -f $i/snmp/include/ucd-snmp/snmp.h && SNMP_INCDIR=$i/snmp/include/ucd-snmp
       done
-      for i in /usr/$PHP_LIBDIR /usr/snmp/lib /usr/local/$PHP_LIBDIR /usr/local/lib /usr/local/snmp/lib; do
+      for i in /usr/$PHP_LIBDIR /usr/snmp/lib /usr/local/$PHP_LIBDIR /usr/local/lib /usr/local/snmp/lib /opt/local/lib /opt/local/$PHP_LIBDIR; do
         test -f $i/libsnmp.a || test -f $i/libsnmp.$SHLIB_SUFFIX_NAME && SNMP_LIBDIR=$i
       done
     else
