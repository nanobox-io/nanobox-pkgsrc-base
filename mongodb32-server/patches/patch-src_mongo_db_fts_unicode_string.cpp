$NetBSD$

--- src/mongo/db/fts/unicode/string.cpp.orig	2017-01-25 15:43:56.000000000 +0000
+++ src/mongo/db/fts/unicode/string.cpp
@@ -274,7 +274,7 @@ bool String::substrMatch(const std::stri
 
     // Case sensitive and diacritic sensitive.
     return boost::algorithm::boyer_moore_search(
-               haystack.begin(), haystack.end(), needle.begin(), needle.end()) != haystack.end();
+               haystack.begin(), haystack.end(), needle.begin(), needle.end()) != std::make_pair(haystack.end(), haystack.end());
 }
 
 }  // namespace unicode
