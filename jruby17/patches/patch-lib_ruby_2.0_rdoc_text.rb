$NetBSD$

--- lib/ruby/2.0/rdoc/text.rb.orig	2015-08-20 17:02:22.000000000 +0000
+++ lib/ruby/2.0/rdoc/text.rb
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
