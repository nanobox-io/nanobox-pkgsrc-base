$NetBSD$

--- src/mongo/db/repl/replica_set_config.cpp.orig	2017-05-01 20:06:54.000000000 +0000
+++ src/mongo/db/repl/replica_set_config.cpp
@@ -490,7 +490,7 @@ BSONObj ReplicaSetConfig::toBSON() const
 
     BSONObjBuilder settingsBuilder(configBuilder.subobjStart("settings"));
     settingsBuilder.append("chainingAllowed", _chainingAllowed);
-    settingsBuilder.append("heartbeatTimeoutSecs", _heartbeatTimeoutPeriod.total_seconds());
+    settingsBuilder.appendIntOrLL("heartbeatTimeoutSecs", _heartbeatTimeoutPeriod.total_seconds());
 
     BSONObjBuilder gleModes(settingsBuilder.subobjStart("getLastErrorModes"));
     for (StringMap<ReplicaSetTagPattern>::const_iterator mode = _customWriteConcernModes.begin();
