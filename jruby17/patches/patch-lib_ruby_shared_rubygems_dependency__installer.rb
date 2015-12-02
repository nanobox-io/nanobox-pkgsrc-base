$NetBSD$

--- lib/ruby/shared/rubygems/dependency_installer.rb.orig	2015-08-20 17:02:24.000000000 +0000
+++ lib/ruby/shared/rubygems/dependency_installer.rb
@@ -63,6 +63,7 @@ class Gem::DependencyInstaller
   # :format_executable:: See Gem::Installer#initialize.
   # :ignore_dependencies:: Don't install any dependencies.
   # :install_dir:: See Gem::Installer#install.
+  # :install_root:: See Gem::Installer#install.
   # :prerelease:: Allow prerelease versions.  See #install.
   # :security_policy:: See Gem::Installer::new and Gem::Security.
   # :user_install:: See Gem::Installer.new
@@ -101,7 +102,12 @@ class Gem::DependencyInstaller
     @installed_gems = []
     @toplevel_specs = nil
 
-    @cache_dir = options[:cache_dir] || @install_dir
+    @install_root = options[:install_root] || ""
+    install_dir = @install_dir
+    unless @install_root.nil? or @install_root.empty?
+      install_dir = File.join(@install_root, install_dir)
+    end
+    @cache_dir = options[:cache_dir] || install_dir
 
     @errors = []
   end
@@ -392,6 +398,7 @@ class Gem::DependencyInstaller
       :force               => @force,
       :format_executable   => @format_executable,
       :ignore_dependencies => @ignore_dependencies,
+      :install_root        => @install_root,
       :prerelease          => @prerelease,
       :security_policy     => @security_policy,
       :user_install        => @user_install,
