$NetBSD$

--- src/mongo/db/repl/is_master_response.cpp.orig	2017-05-01 20:06:54.000000000 +0000
+++ src/mongo/db/repl/is_master_response.cpp
@@ -151,7 +151,7 @@ void IsMasterResponse::addToBSON(BSONObj
     if (_buildIndexesSet)
         builder->append(kBuildIndexesFieldName, _buildIndexes);
     if (_slaveDelaySet)
-        builder->append(kSlaveDelayFieldName, _slaveDelay.total_seconds());
+        builder->appendIntOrLL(kSlaveDelayFieldName, _slaveDelay.total_seconds());
     if (_tagsSet) {
         BSONObjBuilder tags(builder->subobjStart(kTagsFieldName));
         for (unordered_map<std::string, std::string>::const_iterator it = _tags.begin();
