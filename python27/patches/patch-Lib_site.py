$NetBSD$

Support multiarch site-packages.

--- Lib/site.py.orig	Thu Sep 27 11:40:46 2012
+++ Lib/site.py	Thu Sep 27 11:44:21 2012
@@ -300,9 +300,13 @@
         if sys.platform in ('os2emx', 'riscos'):
             sitepackages.append(os.path.join(prefix, "Lib", "site-packages"))
         elif os.sep == '/':
+            if sys.maxsize > 2**32:
+              libarchsuffix = "@LIBARCHSUFFIX.64@".lstrip('/')
+            else:
+              libarchsuffix = "@LIBARCHSUFFIX.32@".lstrip('/')
             sitepackages.append(os.path.join(prefix, "lib",
                                         "python" + sys.version[:3],
-                                        "site-packages"))
+                                        "site-packages", libarchsuffix).rstrip('/'))
             sitepackages.append(os.path.join(prefix, "lib", "site-python"))
         else:
             sitepackages.append(prefix)
