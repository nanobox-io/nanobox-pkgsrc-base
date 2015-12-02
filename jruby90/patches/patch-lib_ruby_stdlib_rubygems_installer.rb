$NetBSD$

--- lib/ruby/stdlib/rubygems/installer.rb.orig	2015-10-21 14:47:54.000000000 +0000
+++ lib/ruby/stdlib/rubygems/installer.rb
@@ -112,6 +112,9 @@ class Gem::Installer
   #                      If your Ruby is ruby18, foo_exec will be installed as
   #                      foo_exec18.
   # :ignore_dependencies:: Don't raise if a dependency is missing.
+  # :install_root:: The directory to use as a buildroot for "destdir"-style
+  #		  installation.  All paths during installation are relative
+  #               to the buildroot.
   # :install_dir:: The directory to install the gem into.
   # :security_policy:: Use the specified security policy.  See Gem::Security
   # :user_install:: Indicate that the gem should be unpacked into the users
@@ -407,9 +410,13 @@ class Gem::Installer
 
   def generate_bin # :nodoc:
     return if spec.executables.nil? or spec.executables.empty?
+    bindir = @bin_dir ? @bin_dir : (Gem.bindir @gem_home, @install_root)
+    unless @install_root.nil? or @install_root.empty?
+      bindir = File.join(@install_root, bindir)
+    end
 
-    Dir.mkdir @bin_dir unless File.exist? @bin_dir
-    raise Gem::FilePermissionError.new(@bin_dir) unless File.writable? @bin_dir
+    Dir.mkdir bindir unless File.exist? bindir
+    raise Gem::FilePermissionError.new(bindir) unless File.writable? bindir
 
     spec.executables.each do |filename|
       filename.untaint
@@ -427,9 +434,9 @@ class Gem::Installer
       check_executable_overwrite filename
 
       if @wrappers then
-        generate_bin_script filename, @bin_dir
+        generate_bin_script filename, bindir
       else
-        generate_bin_symlink filename, @bin_dir
+        generate_bin_symlink filename, bindir
       end
 
     end
@@ -602,7 +609,13 @@ class Gem::Installer
     # If the user has asked for the gem to be installed in a directory that is
     # the system gem directory, then use the system bin directory, else create
     # (or use) a new bin dir under the gem_home.
-    @bin_dir             = options[:bin_dir] || Gem.bindir(gem_home)
+    install_root         = options[:install_root]
+    @bin_dir             = options[:bin_dir] || Gem.bindir(gem_home, install_root)
+    @development         = options[:development]
+    unless install_root.nil? or install_root.empty?
+      @install_root = File.expand_path install_root
+      @gem_home = File.join(@install_root, @gem_home)
+    end
     @development         = options[:development]
     @build_root          = options[:build_root]
 
@@ -794,6 +807,9 @@ TEXT
     return if @build_args.empty?
 
     build_info_dir = File.join gem_home, 'build_info'
+    unless @install_root.nil? or @install_root.empty?
+      build_info_dir = File.join @gem_home, "build_info"
+    end
 
     FileUtils.mkdir_p build_info_dir
 
