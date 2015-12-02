$NetBSD$

--- lib/ruby/stdlib/rdoc/ri/driver.rb.orig	2015-10-21 14:47:54.000000000 +0000
+++ lib/ruby/stdlib/rdoc/ri/driver.rb
@@ -2,11 +2,6 @@ require 'abbrev'
 require 'optparse'
 
 begin
-  require 'readline'
-rescue LoadError
-end
-
-begin
   require 'win32console'
 rescue LoadError
 end
@@ -1069,6 +1064,10 @@ The ri pager can be set with the 'RI_PAG
   # Runs ri interactively using Readline if it is available.
 
   def interactive
+    begin
+      require 'readline'
+    rescue LoadError
+    end
     puts "\nEnter the method name you want to look up."
 
     if defined? Readline then
