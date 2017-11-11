$NetBSD$

--- src/compiler/crystal/codegen/link.cr.orig	2017-10-27 16:40:06.000000000 +0000
+++ src/compiler/crystal/codegen/link.cr
@@ -100,7 +100,7 @@ module Crystal
     end
 
     private def lib_flags_posix
-      library_path = ["/usr/lib", "/usr/local/lib"]
+      library_path = ["/data/lib", "/usr/lib", "/usr/local/lib"]
       has_pkg_config = nil
 
       String.build do |flags|
@@ -131,7 +131,7 @@ module Crystal
         # Append the default paths as -L flags in case the linker doesn't know
         # about them (eg: FreeBSD won't search /usr/local/lib by default):
         library_path.each do |path|
-          flags << " -L#{path}"
+          flags << " -L#{path} -Wl,-rpath #{path}"
         end
       end
     end
