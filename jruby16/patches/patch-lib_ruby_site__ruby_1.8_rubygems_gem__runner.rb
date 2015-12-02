$NetBSD$

--- lib/ruby/site_ruby/1.8/rubygems/gem_runner.rb.orig	2012-09-18 16:37:31.000000000 +0000
+++ lib/ruby/site_ruby/1.8/rubygems/gem_runner.rb
@@ -62,7 +62,7 @@ class Gem::GemRunner
       Gem::Command.add_specific_extra_args command_name, config_args
     end
 
-    cmd.run Gem.configuration.args
+    cmd.run Gem.configuration.args, build_args
     end_time = Time.now
 
     if Gem.configuration.benchmark then
