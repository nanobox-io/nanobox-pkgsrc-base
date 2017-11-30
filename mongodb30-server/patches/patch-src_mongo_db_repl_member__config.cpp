$NetBSD$

--- src/mongo/db/repl/member_config.cpp.orig	2017-05-01 20:06:54.000000000 +0000
+++ src/mongo/db/repl/member_config.cpp
@@ -297,7 +297,7 @@ BSONObj MemberConfig::toBSON(const Repli
     }
     tags.done();
 
-    configBuilder.append("slaveDelay", _slaveDelay.total_seconds());
+    configBuilder.appendIntOrLL("slaveDelay", _slaveDelay.total_seconds());
     configBuilder.append("votes", getNumVotes());
     return configBuilder.obj();
 }
