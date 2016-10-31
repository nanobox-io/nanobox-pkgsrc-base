$NetBSD$

--- lib/rubygems/remote_fetcher.rb.orig	2015-12-16 05:07:31.000000000 +0000
+++ lib/rubygems/remote_fetcher.rb
@@ -324,7 +324,7 @@ class Gem::RemoteFetcher
     if update and path
       begin
         open(path, 'wb') do |io|
-          io.flock(File::LOCK_EX)
+          # io.flock(File::LOCK_EX)
           io.write data
         end
       rescue Errno::ENOLCK # NFS
