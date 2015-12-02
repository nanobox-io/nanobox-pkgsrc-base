$NetBSD$

--- lib/ruby/site_ruby/1.8/rubygems/commands/uninstall_command.rb.orig	2012-09-18 16:37:31.000000000 +0000
+++ lib/ruby/site_ruby/1.8/rubygems/commands/uninstall_command.rb
@@ -21,6 +21,11 @@ class Gem::Commands::UninstallCommand <
       options[:all] = value
     end
 
+    add_option('-B', '--install-root DIR',
+               'Root directory for gem files') do |value, options|
+      options[:install_root] = File.expand_path(value)
+    end
+
     add_option('-I', '--[no-]ignore-dependencies',
                'Ignore dependency requirements while',
                'uninstalling') do |value, options|
