$NetBSD$

--- lib/ruby/shared/rubygems/commands/uninstall_command.rb.orig	2015-08-20 17:02:24.000000000 +0000
+++ lib/ruby/shared/rubygems/commands/uninstall_command.rb
@@ -23,6 +23,11 @@ class Gem::Commands::UninstallCommand <
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
