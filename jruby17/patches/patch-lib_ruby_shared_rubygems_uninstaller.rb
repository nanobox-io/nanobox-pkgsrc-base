$NetBSD$

--- lib/ruby/shared/rubygems/uninstaller.rb.orig	2015-08-20 17:02:24.000000000 +0000
+++ lib/ruby/shared/rubygems/uninstaller.rb
@@ -51,6 +51,11 @@ class Gem::Uninstaller
     @force_ignore       = options[:ignore]
     @bin_dir            = options[:bin_dir]
     @format_executable  = options[:format_executable]
+    install_root = options[:install_root]
+    unless install_root.nil? or install_root.empty?
+      @install_root = File.expand_path install_root
+      @gem_home = File.join(@install_root, @gem_home)
+    end
     @abort_on_dependent = options[:abort_on_dependent]
 
     # Indicate if development dependencies should be checked when
@@ -203,7 +208,11 @@ class Gem::Uninstaller
              end
 
     if remove then
-      bin_dir = @bin_dir || Gem.bindir(spec.base_dir)
+      bin_dir = @bin_dir || (Gem.bindir @gem_home, @install_root)
+
+      unless @install_root.nil? or @install_root.empty?
+        bindir = File.join(@install_root, bindir)
+      end
 
       raise Gem::FilePermissionError, bin_dir unless File.writable? bin_dir
 
