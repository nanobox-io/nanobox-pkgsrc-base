$NetBSD$

--- lib/ruby/stdlib/rdoc/text.rb.orig	2015-10-21 14:47:54.000000000 +0000
+++ lib/ruby/stdlib/rdoc/text.rb
@@ -68,11 +68,11 @@ module RDoc::Text
     expanded = []
 
     text.each_line do |line|
-      line.gsub!(/^((?:.{8})*?)([^\t\r\n]{0,7})\t/) do
+      nil while line.gsub!(/(?:\G|\r)((?:.{8})*?)([^\t\r\n]{0,7})\t/) do
         r = "#{$1}#{$2}#{' ' * (8 - $2.size)}"
         r.force_encoding text.encoding if Object.const_defined? :Encoding
         r
-      end until line !~ /\t/
+      end
 
       expanded << line
     end
