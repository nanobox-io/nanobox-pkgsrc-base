$NetBSD$

--- lib/ruby/stdlib/rubygems/defaults.rb.orig	2015-10-21 14:47:54.000000000 +0000
+++ lib/ruby/stdlib/rubygems/defaults.rb
@@ -29,7 +29,7 @@ module Gem
   def self.default_dir
     path = if defined? RUBY_FRAMEWORK_VERSION then
              [
-               File.dirname(RbConfig::CONFIG['sitedir']),
+               File.dirname(RbConfig::CONFIG['vendordir']),
                'Gems',
                RbConfig::CONFIG['ruby_version']
              ]
