$NetBSD$

--- site_scons/mongo/__init__.py.orig	2018-01-04 23:28:55.000000000 +0000
+++ site_scons/mongo/__init__.py
@@ -5,4 +5,4 @@
 def print_build_failures():
     from SCons.Script import GetBuildFailures
     for bf in GetBuildFailures():
-        print "%s failed: %s" % (bf.node, bf.errstr)
+        print("%s failed: %s" % (bf.node, bf.errstr))
