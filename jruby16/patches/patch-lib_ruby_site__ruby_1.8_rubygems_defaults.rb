$NetBSD$

--- lib/ruby/site_ruby/1.8/rubygems/defaults.rb.orig	2012-09-18 16:37:31.000000000 +0000
+++ lib/ruby/site_ruby/1.8/rubygems/defaults.rb
@@ -21,7 +21,7 @@ module Gem
   def self.default_dir
     path = if defined? RUBY_FRAMEWORK_VERSION then
              [
-               File.dirname(ConfigMap[:sitedir]),
+               File.dirname(ConfigMap[:vendordir]),
                'Gems',
                ConfigMap[:ruby_version]
              ]
