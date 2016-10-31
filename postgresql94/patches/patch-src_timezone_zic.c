$NetBSD$

--- src/timezone/zic.c.orig	2016-08-08 20:29:39.000000000 +0000
+++ src/timezone/zic.c
@@ -109,35 +109,35 @@ static void warning(const char *string,.
 __attribute__((format(PG_PRINTF_ATTRIBUTE, 1, 2)));
 static void usage(FILE *stream, int status) __attribute__((noreturn));
 static void addtt(zic_t starttime, int type);
-static int	addtype(zic_t, char const *, bool, bool, bool);
-static void leapadd(zic_t, bool, int, int);
+static int	addtype(zic_t, char const *, const bool, const bool, const bool);
+static void leapadd(zic_t, const bool, const int, const int);
 static void adjleap(void);
 static void associate(void);
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
@@ -432,7 +432,7 @@ growalloc(void *ptr, size_t itemsize, in
  */
 
 static void
-eats(const char *name, int num, const char *rname, int rnum)
+eats(const char *name, const int num, const char *rname, const int rnum)
 {
 	filename = name;
 	linenum = num;
@@ -441,7 +441,7 @@ eats(const char *name, int num, const ch
 }
 
 static void
-eat(const char *name, int num)
+eat(const char *name, const int num)
 {
 	eats(name, num, NULL, -1);
 }
@@ -1150,7 +1150,7 @@ infile(const char *name)
  * Call error with errstring and return zero on errors.
  */
 static zic_t
-gethms(char const * string, char const * errstring, bool signable)
+gethms(char const * string, char const * errstring, const bool signable)
 {
 	/* PG: make hh be int not zic_t to avoid sscanf portability issues */
 	int			hh;
