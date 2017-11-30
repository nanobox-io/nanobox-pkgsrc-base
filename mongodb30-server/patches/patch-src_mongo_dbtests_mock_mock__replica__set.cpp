$NetBSD$

--- src/mongo/dbtests/mock/mock_replica_set.cpp.orig	2017-05-01 20:06:54.000000000 +0000
+++ src/mongo/dbtests/mock/mock_replica_set.cpp
@@ -216,7 +216,7 @@ void MockReplicaSet::mockIsMasterCmd() {
             }
 
             if (member->getSlaveDelay().total_seconds()) {
-                builder.append("slaveDelay", member->getSlaveDelay().total_seconds());
+                builder.appendIntOrLL("slaveDelay", member->getSlaveDelay().total_seconds());
             }
 
             if (member->isHidden()) {
