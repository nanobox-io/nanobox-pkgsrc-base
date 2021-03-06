$NetBSD$

--- lib/ruby/shared/rubygems.rb.orig	2015-08-20 17:02:24.000000000 +0000
+++ lib/ruby/shared/rubygems.rb
@@ -265,10 +265,16 @@ module Gem
   ##
   # The path where gem executables are to be installed.
 
-  def self.bindir(install_dir=Gem.dir)
-    return File.join install_dir, 'bin' unless
-      install_dir.to_s == Gem.default_dir.to_s
-    Gem.default_bindir
+  def self.bindir(install_dir=Gem.dir, install_root=nil)
+    if install_dir.to_s == Gem.default_dir.to_s
+      install_dir = Gem.default_bindir
+    else
+      install_dir = File.join install_dir, 'bin'
+    end
+    unless install_root.nil? or install_root.empty?
+      install_dir = File.join install_root, install_dir
+    end
+    install_dir
   end
 
   ##
@@ -580,7 +586,7 @@ module Gem
   # gem's paths are inserted before site lib directory by default.
 
   def self.load_path_insert_index
-    index = $LOAD_PATH.index RbConfig::CONFIG['sitelibdir']
+    index = $LOAD_PATH.index RbConfig::CONFIG['vendorlibdir']
 
     index
   end
@@ -752,6 +758,7 @@ module Gem
     prefix = File.dirname RUBYGEMS_DIR
 
     if prefix != File.expand_path(RbConfig::CONFIG['sitelibdir']) and
+       prefix != File.expand_path(RbConfig::CONFIG['vendorlibdir']) and
        prefix != File.expand_path(RbConfig::CONFIG['libdir']) and
        'lib' == File.basename(RUBYGEMS_DIR) then
       prefix
