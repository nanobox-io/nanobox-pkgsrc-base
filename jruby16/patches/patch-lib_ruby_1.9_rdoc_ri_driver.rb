$NetBSD$

--- lib/ruby/1.9/rdoc/ri/driver.rb.orig	2012-09-18 16:37:31.000000000 +0000
+++ lib/ruby/1.9/rdoc/ri/driver.rb
@@ -2,7 +2,7 @@ require 'abbrev'
 require 'optparse'
 
 begin
-  require 'readline'
+  require 'win32console'
 rescue LoadError
 end
 
@@ -809,6 +809,10 @@ Options may also be set in the 'RI' envi
   # Runs ri interactively using Readline if it is available.
 
   def interactive
+    begin
+      require 'readline'
+    rescue LoadError
+    end
     puts "\nEnter the method name you want to look up."
 
     if defined? Readline then
