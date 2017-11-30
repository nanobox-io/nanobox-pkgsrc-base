$NetBSD$

--- tools/install.py.orig	2016-08-26 15:27:23.000000000 +0000
+++ tools/install.py
@@ -98,6 +98,37 @@ def npm_files(action):
   else:
     assert(0) # unhandled action type
 
+def yarn_files(action):
+  target_path = 'lib/node_modules/yarn/'
+
+  # don't install npm if the target path is a symlink, it probably means
+  # that a dev version of npm is installed there
+  if os.path.islink(abspath(install_path, target_path)): return
+
+  # npm has a *lot* of files and it'd be a pain to maintain a fixed list here
+  # so we walk its source directory instead...
+  for dirname, subdirs, basenames in os.walk('deps/yarn', topdown=True):
+    subdirs[:] = filter('test'.__ne__, subdirs) # skip test suites
+    paths = [os.path.join(dirname, basename) for basename in basenames]
+    action(paths, target_path + dirname[9:] + '/')
+
+  # create/remove symlink
+  link_path = abspath(install_path, 'bin/yarn')
+  if action == uninstall:
+    action([link_path], 'bin/yarn')
+  elif action == install:
+    try_symlink('../lib/node_modules/yarn/bin/yarn.js', link_path)
+  else:
+    assert(0) # unhandled action type
+  link_path = abspath(install_path, 'bin/yarnpkg')
+  if action == uninstall:
+    action([link_path], 'bin/yarnpkg')
+  elif action == install:
+    try_symlink('../lib/node_modules/yarn/bin/yarn.js', link_path)
+  else:
+    assert(0) # unhandled action type
+
+
 def subdir_files(path, dest, action):
   ret = {}
   for dirpath, dirnames, filenames in os.walk(path):
@@ -137,9 +168,10 @@ def files(action):
   if 'freebsd' in sys.platform or 'openbsd' in sys.platform:
     action(['doc/node.1'], 'man/man1/')
   else:
-    action(['doc/node.1'], 'share/man/man1/')
+    action(['doc/node.1'], 'man/man1/')
 
   if 'true' == variables.get('node_install_npm'): npm_files(action)
+  if 'true' == variables.get('node_install_npm'): yarn_files(action)
 
   headers(action)
 
