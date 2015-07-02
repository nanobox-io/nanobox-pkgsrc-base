$NetBSD$

--- gcs/src/gcs.cpp.orig	2015-03-25 16:24:41.000000000 +0000
+++ gcs/src/gcs.cpp
@@ -743,7 +743,7 @@ _set_fc_limits (gcs_conn_t* conn)
 {
     /* Killing two birds with one stone: flat FC profile for master-slave setups
      * plus #440: giving single node some slack at some math correctness exp.*/
-    double fn = conn->params.fc_master_slave ? 1.0 : sqrt(conn->memb_num);
+    double fn = conn->params.fc_master_slave ? 1.0 : sqrt((double)conn->memb_num);
 
     conn->upper_limit = conn->params.fc_base_limit * fn + .5;
     conn->lower_limit = conn->upper_limit * conn->params.fc_resume_factor + .5;
