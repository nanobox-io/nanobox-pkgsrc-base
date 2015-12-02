$NetBSD$

--- lib/ruby/shared/rubygems/defaults.rb.orig	2015-08-20 17:02:24.000000000 +0000
+++ lib/ruby/shared/rubygems/defaults.rb
@@ -29,7 +29,7 @@ module Gem
   def self.default_dir
     path = if defined? RUBY_FRAMEWORK_VERSION then
              [
-               File.dirname(RbConfig::CONFIG['sitedir']),
+               File.dirname(RbConfig::CONFIG['vendordir']),
                'Gems',
                RbConfig::CONFIG['ruby_version']
              ]
