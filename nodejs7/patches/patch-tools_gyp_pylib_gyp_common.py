$NetBSD$

--- tools/gyp/pylib/gyp/common.py.orig	2017-07-11 02:46:27.000000000 +0000
+++ tools/gyp/pylib/gyp/common.py
@@ -427,6 +427,8 @@ def GetFlavor(params):
     return 'openbsd'
   if sys.platform.startswith('netbsd'):
     return 'netbsd'
+  if sys.platform.startswith('dragonflybsd'):
+    return 'dragonflybsd'
   if sys.platform.startswith('aix'):
     return 'aix'
 
