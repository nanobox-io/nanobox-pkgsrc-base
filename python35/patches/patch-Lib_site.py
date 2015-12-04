$NetBSD$

--- Lib/site.py.orig	2015-09-13 11:41:21.000000000 +0000
+++ Lib/site.py
@@ -303,9 +303,13 @@ def getsitepackages(prefixes=None):
         seen.add(prefix)
 
         if os.sep == '/':
+            if sys.maxsize > 2**32:
+                libarchsuffix = "@LIBARCHSUFFIX.64@".lstrip('/')
+            else:
+                libarchsuffix = "@LIBARCHSUFFIX.32@".lstrip('/')
             sitepackages.append(os.path.join(prefix, "lib",
                                         "python" + sys.version[:3],
-                                        "site-packages"))
+                                        "site-packages", libarchsuffix).rstrip('/'))
         else:
             sitepackages.append(prefix)
             sitepackages.append(os.path.join(prefix, "lib", "site-packages"))
