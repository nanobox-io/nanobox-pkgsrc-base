$NetBSD$

--- src/mongo/db/repl/repl_set_heartbeat_response.cpp.orig	2017-05-01 20:06:54.000000000 +0000
+++ src/mongo/db/repl/repl_set_heartbeat_response.cpp
@@ -92,7 +92,7 @@ void ReplSetHeartbeatResponse::addToBSON
         builder->appendDate(kOpTimeFieldName, _opTime.asDate());
     }
     if (_timeSet) {
-        *builder << kTimeFieldName << _time.total_seconds();
+        builder->appendIntOrLL(kTimeFieldName, _time.total_seconds());
     }
     if (_electionTimeSet) {
         builder->appendDate(kElectionTimeFieldName, _electionTime.asDate());
