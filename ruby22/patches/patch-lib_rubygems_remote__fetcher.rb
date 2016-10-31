$NetBSD$

--- lib/rubygems/remote_fetcher.rb.orig	2015-08-17 14:20:34.000000000 +0000
+++ lib/rubygems/remote_fetcher.rb
@@ -313,7 +313,7 @@ class Gem::RemoteFetcher
 
     if update and path
       open(path, 'wb') do |io|
-        io.flock(File::LOCK_EX)
+        # io.flock(File::LOCK_EX)
         io.write data
       end
     end
