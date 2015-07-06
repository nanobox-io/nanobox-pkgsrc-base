$NetBSD$

--- src/mongo/db/auth/privilege_set.cpp.orig	2015-04-27 16:18:57.000000000 +0000
+++ src/mongo/db/auth/privilege_set.cpp
@@ -79,7 +79,7 @@ namespace mongo {
         resourceSearchList[1] = nsToDatabaseSubstring(desiredPrivilege.getResource());
 
         ActionSet unmetRequirements = desiredPrivilege.getActions();
-        for (int i = 0; i < boost::size(resourceSearchList); ++i) {
+        for (unsigned int i = 0; i < boost::size(resourceSearchList); ++i) {
             ResourcePrivilegeCacheEntry* entry = _lookupEntry(resourceSearchList[i]);
             if (NULL == entry)
                 continue;
