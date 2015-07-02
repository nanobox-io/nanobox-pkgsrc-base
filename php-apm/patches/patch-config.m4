$NetBSD$

--- config.m4.orig	2013-05-11 17:13:43.000000000 +0000
+++ config.m4
@@ -57,7 +57,7 @@ if test "$PHP_APM" != "no"; then
     sqlite3_driver="driver_sqlite3.c"
     AC_DEFINE(APM_DRIVER_SQLITE3, 1, [activate sqlite3 storage driver])
     AC_MSG_CHECKING([for sqlite3 files in default path])
-    for i in /usr/local /usr; do
+    for i in /usr/local /usr /opt/local; do
       if test -f $i/include/sqlite3.h; then
         SQLITE3_DIR=$i
         AC_MSG_RESULT(found in $i)
@@ -90,7 +90,7 @@ if test "$PHP_APM" != "no"; then
     MYSQL_DIR=
     MYSQL_INC_DIR=
 
-    for i in $PHP_MYSQL /usr/local /usr; do
+    for i in $PHP_MYSQL /usr/local /usr /opt/local; do
       if test -r $i/include/mysql/mysql.h; then
         MYSQL_DIR=$i
         MYSQL_INC_DIR=$i/include/mysql
