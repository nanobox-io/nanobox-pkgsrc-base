$NetBSD$

--- lib/ruby/site_ruby/1.8/rubygems/commands/unpack_command.rb.orig	2012-09-18 16:37:31.000000000 +0000
+++ lib/ruby/site_ruby/1.8/rubygems/commands/unpack_command.rb
@@ -14,6 +14,10 @@ class Gem::Commands::UnpackCommand < Gem
           :version => Gem::Requirement.default,
           :target  => Dir.pwd
 
+    add_option('--install-root DIR', 'Root directory for gem files on extract') do |value, options|
+      options[:install_root] = value
+    end
+
     add_option('--target=DIR',
                'target directory for unpacking') do |value, options|
       options[:target] = value
@@ -70,7 +74,8 @@ class Gem::Commands::UnpackCommand < Gem
         basename = File.basename path, '.gem'
         target_dir = File.expand_path basename, options[:target]
         FileUtils.mkdir_p target_dir
-        Gem::Installer.new(path, :unpack => true).unpack target_dir
+        Gem::Installer.new(path, :unpack => true,
+                     :install_root => options[:install_root]).unpack target_dir
         say "Unpacked gem: '#{target_dir}'"
       end
     end
