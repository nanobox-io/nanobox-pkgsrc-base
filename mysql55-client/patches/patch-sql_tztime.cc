$NetBSD$

--- sql/tztime.cc.orig	2014-06-18 15:59:42.959623032 +0000
+++ sql/tztime.cc
@@ -2534,7 +2534,8 @@ main(int argc, char **argv)
   }
 
   // Replicate MyISAM DDL for this session, cf. lp:1161432
-  printf("SET SESSION wsrep_replicate_myisam=ON;\n");
+  // wsrep_replicate_myisam is not a session variable
+  // printf("SET SESSION wsrep_replicate_myisam=ON;\n");
 
   if (argc == 2)
   {
