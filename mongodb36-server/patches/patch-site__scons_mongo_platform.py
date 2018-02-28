$NetBSD$

--- site_scons/mongo/platform.py.orig	2018-01-04 23:28:55.000000000 +0000
+++ site_scons/mongo/platform.py
@@ -20,8 +20,12 @@ def get_running_os_name():
     running_os = os.sys.platform
     if running_os.startswith('linux'):
         running_os = 'linux'
+    elif running_os.startswith('dragonfly'):
+        running_os = 'dragonfly'
     elif running_os.startswith('freebsd'):
         running_os = 'freebsd'
+    elif running_os.startswith('netbsd'):
+        running_os = 'netbsd'
     elif running_os.startswith('openbsd'):
         running_os = 'openbsd'
     elif running_os == 'sunos5':
@@ -41,7 +45,7 @@ def is_os_raw(target_os, os_list_to_chec
     okay = False
 
     darwin_os_list = [ 'macOS', 'tvOS', 'tvOS-sim', 'iOS', 'iOS-sim' ]
-    posix_os_list = [ 'linux', 'openbsd', 'freebsd', 'solaris' ] + darwin_os_list
+    posix_os_list = [ 'linux', 'openbsd', 'freebsd', 'solaris', 'dragonfly', 'netbsd' ] + darwin_os_list
 
     for p in os_list_to_check:
         if p == 'posix' and target_os in posix_os_list:
