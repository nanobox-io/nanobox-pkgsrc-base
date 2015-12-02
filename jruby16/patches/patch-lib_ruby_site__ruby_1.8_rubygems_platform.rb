$NetBSD$

--- lib/ruby/site_ruby/1.8/rubygems/platform.rb.orig	2012-09-18 16:37:31.000000000 +0000
+++ lib/ruby/site_ruby/1.8/rubygems/platform.rb
@@ -51,10 +51,7 @@ class Gem::Platform
 
       cpu = arch.shift
 
-      @cpu = case cpu
-             when /i\d86/ then 'x86'
-             else cpu
-             end
+      @cpu = cpu
 
       if arch.length == 2 and arch.last =~ /^\d+(\.\d+)?$/ then # for command-line
         @os, @version = arch
@@ -81,7 +78,7 @@ class Gem::Platform
                         os, version = $1, $3
                         @cpu = 'x86' if @cpu.nil? and os =~ /32$/
                         [os, version]
-                      when /netbsdelf/ then            [ 'netbsdelf', nil ]
+                      when /netbsd/ then               [ 'netbsd',    nil ]
                       when /openbsd(\d+\.\d+)/ then    [ 'openbsd',   $1  ]
                       when /solaris(\d+\.\d+)/ then    [ 'solaris',   $1  ]
                       # test
