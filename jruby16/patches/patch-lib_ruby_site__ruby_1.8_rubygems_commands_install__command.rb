$NetBSD$

--- lib/ruby/site_ruby/1.8/rubygems/commands/install_command.rb.orig	2012-09-18 16:37:31.000000000 +0000
+++ lib/ruby/site_ruby/1.8/rubygems/commands/install_command.rb
@@ -148,7 +148,7 @@ to write the specification by hand.  For
           Gem::DocManager.new(gem, options[:rdoc_args]).generate_ri
         end
 
-        Gem::DocManager.update_ri_cache
+        Gem::DocManager.update_ri_cache(options[:install_root])
       end
 
       if options[:generate_rdoc] then
