$NetBSD$

--- src/timezone/zic.c.orig	2016-08-08 20:31:43.000000000 +0000
+++ src/timezone/zic.c
@@ -120,28 +120,28 @@ static void associate(void);
 static void dolink(const char *fromfield, const char *tofield);
 static char **getfields(char *buf);
 static zic_t gethms(const char *string, const char *errstring,
-	   bool);
+	   const bool);
 static void infile(const char *filename);
-static void inleap(char **fields, int nfields);
-static void inlink(char **fields, int nfields);
-static void inrule(char **fields, int nfields);
-static bool inzcont(char **fields, int nfields);
-static bool inzone(char **fields, int nfields);
-static bool inzsub(char **, int, bool);
+static void inleap(char **fields, const int nfields);
+static void inlink(char **fields, const int nfields);
+static void inrule(char **fields, const int nfields);
+static bool inzcont(char **fields, const int nfields);
+static bool inzone(char **fields, const int nfields);
+static bool inzsub(char **, const int, const bool);
 static int	itsdir(const char *name);
 static bool is_alpha(char a);
 static char lowerit(char);
 static bool mkdirs(char *);
 static void newabbr(const char *abbr);
 static zic_t oadd(zic_t t1, zic_t t2);
-static void outzone(const struct zone * zp, int ntzones);
+static void outzone(const struct zone * zp, const int ntzones);
 static zic_t rpytime(const struct rule * rp, zic_t wantedy);
 static void rulesub(struct rule * rp,
 		const char *loyearp, const char *hiyearp,
 		const char *typep, const char *monthp,
 		const char *dayp, const char *timep);
 static zic_t tadd(zic_t t1, zic_t t2);
-static bool yearistype(int year, const char *type);
+static bool yearistype(const int year, const char *type);
 
 /* Bound on length of what %z can expand to.  */
 enum
@@ -436,7 +436,7 @@ growalloc(void *ptr, size_t itemsize, in
  */
 
 static void
-eats(const char *name, int num, const char *rname, int rnum)
+eats(const char *name, const int num, const char *rname, const int rnum)
 {
 	filename = name;
 	linenum = num;
@@ -445,7 +445,7 @@ eats(const char *name, int num, const ch
 }
 
 static void
-eat(const char *name, int num)
+eat(const char *name, const int num)
 {
 	eats(name, num, NULL, -1);
 }
@@ -1154,7 +1154,7 @@ infile(const char *name)
  * Call error with errstring and return zero on errors.
  */
 static zic_t
-gethms(char const * string, char const * errstring, bool signable)
+gethms(char const * string, char const * errstring, const bool signable)
 {
 	/* PG: make hh be int not zic_t to avoid sscanf portability issues */
 	int			hh;
