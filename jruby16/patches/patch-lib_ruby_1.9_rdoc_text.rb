$NetBSD$

--- lib/ruby/1.9/rdoc/text.rb.orig	2012-09-18 16:37:31.000000000 +0000
+++ lib/ruby/1.9/rdoc/text.rb
@@ -10,9 +10,11 @@ module RDoc::Text
     expanded = []
 
     text.each_line do |line|
-      line.gsub!(/^(.{8}*?)([^\t\r\n]{0,7})\t/) do
-        "#{$1}#{$2}#{' ' * (8 - $2.size)}"
-      end until line !~ /\t/
+      nil while line.gsub!(/(?:\G|\r)((?:.{8})*?)([^\t\r\n]{0,7})\t/) do
+        r = "#{$1}#{$2}#{' ' * (8 - $2.size)}"
+        r.force_encoding text.encoding if Object.const_defined? :Encoding
+        r
+      end
 
       expanded << line
     end
