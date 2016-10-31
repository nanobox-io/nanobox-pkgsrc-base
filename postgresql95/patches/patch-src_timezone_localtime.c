$NetBSD$

--- src/timezone/localtime.c.orig	2016-08-08 20:27:53.000000000 +0000
+++ src/timezone/localtime.c
@@ -623,7 +623,7 @@ getqzname(const char *strp, int delim)
  * Otherwise, return a pointer to the first character not part of the number.
  */
 static const char *
-getnum(const char *strp, int *nump, int min, int max)
+getnum(const char *strp, int *nump, const int min, const int max)
 {
 	char		c;
 	int			num;
@@ -778,8 +778,8 @@ getrule(const char *strp, struct rule *
  * effect, calculate the year-relative time that rule takes effect.
  */
 static int32
-transtime(int year, const struct rule * rulep,
-		  int32 offset)
+transtime(const int year, const struct rule * rulep,
+		  const int32 offset)
 {
 	bool		leapyear;
 	int32		value;
@@ -1263,7 +1263,7 @@ pg_localtime(const pg_time_t *timep, con
  * Except we have a private "struct state" for GMT, so no sp is passed in.
  */
 static struct pg_tm *
-gmtsub(pg_time_t const * timep, int32 offset, struct pg_tm * tmp)
+gmtsub(pg_time_t const * timep, const int32 offset, struct pg_tm * tmp)
 {
 	struct pg_tm *result;
 
@@ -1310,7 +1310,7 @@ leaps_thru_end_of(const int y)
 }
 
 static struct pg_tm *
-timesub(const pg_time_t *timep, int32 offset,
+timesub(const pg_time_t *timep, const int32 offset,
 		const struct state * sp, struct pg_tm * tmp)
 {
 	const struct lsinfo *lp;
