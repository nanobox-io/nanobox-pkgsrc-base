$NetBSD$

--- lib/rubygems/remote_fetcher.rb.orig	2015-08-18 12:56:58.000000000 +0000
+++ lib/rubygems/remote_fetcher.rb
@@ -307,7 +307,7 @@ class Gem::RemoteFetcher
 
     if update and path
       open(path, 'wb') do |io|
-        io.flock(File::LOCK_EX)
+        # io.flock(File::LOCK_EX)
         io.write data
       end
     end
