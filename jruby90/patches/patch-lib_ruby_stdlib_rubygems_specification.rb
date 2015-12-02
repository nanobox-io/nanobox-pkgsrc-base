$NetBSD$

--- lib/ruby/stdlib/rubygems/specification.rb.orig	2015-10-21 14:47:54.000000000 +0000
+++ lib/ruby/stdlib/rubygems/specification.rb
@@ -2647,7 +2647,7 @@ http://opensource.org/licenses/alphabeti
 
     dependencies.each do |dep|
       if prev = seen[dep.name] then
-        raise Gem::InvalidSpecificationException, <<-MESSAGE
+        warn <<-MESSAGE
 duplicate dependency on #{dep}, (#{prev.requirement}) use:
     add_runtime_dependency '#{dep.name}', '#{dep.requirement}', '#{prev.requirement}'
         MESSAGE
