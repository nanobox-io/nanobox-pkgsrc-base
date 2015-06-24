$NetBSD$

--- src/mongo/util/time_support.h.orig	2013-10-31 14:15:50.000000000 +0000
+++ src/mongo/util/time_support.h
@@ -96,10 +96,6 @@ namespace mongo {
     struct tm *gmtime(const time_t *timep);
     struct tm *localtime(const time_t *timep);
 
-#if defined(MONGO_BOOST_TIME_UTC_HACK) || (BOOST_VERSION >= 105000)
 #define MONGO_BOOST_TIME_UTC boost::TIME_UTC_
-#else
-#define MONGO_BOOST_TIME_UTC boost::TIME_UTC
-#endif
 
 }  // namespace mongo
