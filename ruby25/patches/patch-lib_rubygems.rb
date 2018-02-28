$NetBSD$

--- lib/rubygems.rb.orig	2016-10-30 06:32:48.000000000 +0000
+++ lib/rubygems.rb
@@ -310,10 +310,16 @@ module Gem
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
@@ -653,7 +659,7 @@ An Array (#{env.inspect}) was passed in
       return i if path.instance_variable_defined?(:@gem_prelude_index)
     end
 
-    index = $LOAD_PATH.index RbConfig::CONFIG['sitelibdir']
+    index = $LOAD_PATH.index RbConfig::CONFIG['vendorlibdir']
 
     index
   end
@@ -828,6 +834,7 @@ An Array (#{env.inspect}) was passed in
     prefix = File.dirname RUBYGEMS_DIR
 
     if prefix != File.expand_path(RbConfig::CONFIG['sitelibdir']) and
+       prefix != File.expand_path(ConfigMap[:vendorlibdir]) and
        prefix != File.expand_path(RbConfig::CONFIG['libdir']) and
        'lib' == File.basename(RUBYGEMS_DIR) then
       prefix
@@ -846,7 +853,7 @@ An Array (#{env.inspect}) was passed in
 
   def self.read_binary(path)
     open path, 'rb+' do |f|
-      f.flock(File::LOCK_EX)
+      #f.flock(File::LOCK_EX)
       f.read
     end
   rescue *READ_BINARY_ERRORS
@@ -868,7 +875,7 @@ An Array (#{env.inspect}) was passed in
   def self.write_binary(path, data)
     open(path, 'wb') do |io|
       begin
-        io.flock(File::LOCK_EX)
+        #io.flock(File::LOCK_EX)
       rescue *WRITE_BINARY_ERRORS
       end
       io.write data
