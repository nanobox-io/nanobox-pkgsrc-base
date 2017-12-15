$NetBSD$

--- src/odbc/odbc.c.orig	2004-05-30 08:06:43.000000000 +0000
+++ src/odbc/odbc.c
@@ -211,7 +211,7 @@ SQLRETURN SQL_API SQLDescribeParam(
     SQLHSTMT           hstmt,
     SQLUSMALLINT       ipar,
     SQLSMALLINT FAR   *pfSqlType,
-    SQLUINTEGER FAR   *pcbParamDef,
+    SQLULEN FAR   *pcbParamDef,
     SQLSMALLINT FAR   *pibScale,
     SQLSMALLINT FAR   *pfNullable)
 {
@@ -222,8 +222,8 @@ SQLRETURN SQL_API SQLDescribeParam(
 SQLRETURN SQL_API SQLExtendedFetch(
     SQLHSTMT           hstmt,
     SQLUSMALLINT       fFetchType,
-    SQLINTEGER         irow,
-    SQLUINTEGER FAR   *pcrow,
+    SQLLEN         irow,
+    SQLULEN FAR   *pcrow,
     SQLUSMALLINT FAR  *rgfRowStatus)
 {
 struct _hstmt *stmt = (struct _hstmt *) hstmt;
@@ -298,8 +298,8 @@ SQLRETURN SQL_API SQLNumParams(
 
 SQLRETURN SQL_API SQLParamOptions(
     SQLHSTMT           hstmt,
-    SQLUINTEGER        crow,
-    SQLUINTEGER FAR   *pirow)
+    SQLULEN        crow,
+    SQLULEN FAR   *pirow)
 {
 	TRACE("SQLParamOptions");
 	return SQL_SUCCESS;
@@ -348,7 +348,7 @@ SQLRETURN SQL_API SQLProcedures(
 
 SQLRETURN SQL_API SQLSetPos(
     SQLHSTMT           hstmt,
-    SQLUSMALLINT       irow,
+    SQLSETPOSIROW       irow,
     SQLUSMALLINT       fOption,
     SQLUSMALLINT       fLock)
 {
@@ -399,11 +399,11 @@ SQLRETURN SQL_API SQLBindParameter(
     SQLSMALLINT        fParamType,
     SQLSMALLINT        fCType,
     SQLSMALLINT        fSqlType,
-    SQLUINTEGER        cbColDef,
+    SQLULEN        cbColDef,
     SQLSMALLINT        ibScale,
     SQLPOINTER         rgbValue,
-    SQLINTEGER         cbValueMax,
-    SQLINTEGER FAR    *pcbValue)
+    SQLLEN         cbValueMax,
+    SQLLEN FAR    *pcbValue)
 {
 struct _hstmt *stmt;
 
@@ -503,8 +503,8 @@ SQLRETURN SQL_API SQLBindCol(
     SQLUSMALLINT       icol,
     SQLSMALLINT        fCType,
     SQLPOINTER         rgbValue,
-    SQLINTEGER         cbValueMax,
-    SQLINTEGER FAR    *pcbValue)
+    SQLLEN         cbValueMax,
+    SQLLEN FAR    *pcbValue)
 {
 	struct _hstmt *stmt = (struct _hstmt *) hstmt;
 	struct _sql_bind_info *cur, *newitem;
@@ -593,7 +593,7 @@ SQLRETURN SQL_API SQLDescribeCol(
     SQLSMALLINT        cbColNameMax,
     SQLSMALLINT FAR   *pcbColName,
     SQLSMALLINT FAR   *pfSqlType,
-    SQLUINTEGER FAR   *pcbColDef, /* precision */
+    SQLULEN FAR   *pcbColDef, /* precision */
     SQLSMALLINT FAR   *pibScale,
     SQLSMALLINT FAR   *pfNullable)
 {
@@ -648,7 +648,7 @@ SQLRETURN SQL_API SQLColAttributes(
     SQLPOINTER         rgbDesc,
     SQLSMALLINT        cbDescMax,
     SQLSMALLINT FAR   *pcbDesc,
-    SQLINTEGER FAR    *pfDesc)
+    SQLLEN FAR    *pfDesc)
 {
 	int namelen, i;
 	struct _hstmt *stmt;
@@ -988,7 +988,7 @@ SQLRETURN SQL_API SQLPrepare(
 
 SQLRETURN SQL_API SQLRowCount(
     SQLHSTMT           hstmt,
-    SQLINTEGER FAR    *pcrow)
+    SQLLEN FAR    *pcrow)
 {
 struct _hstmt *stmt=(struct _hstmt *)hstmt;
 
@@ -1021,10 +1021,10 @@ SQLRETURN SQL_API SQLSetParam(
     SQLUSMALLINT       ipar,
     SQLSMALLINT        fCType,
     SQLSMALLINT        fSqlType,
-    SQLUINTEGER        cbParamDef,
+    SQLULEN        cbParamDef,
     SQLSMALLINT        ibScale,
     SQLPOINTER         rgbValue,
-    SQLINTEGER FAR     *pcbValue)
+    SQLLEN FAR     *pcbValue)
 {
 	TRACE("SQLSetParam");
 	return SQL_SUCCESS;
@@ -1059,8 +1059,8 @@ SQLRETURN SQL_API SQLGetData(
     SQLUSMALLINT       icol,
     SQLSMALLINT        fCType,
     SQLPOINTER         rgbValue,
-    SQLINTEGER         cbValueMax,
-    SQLINTEGER FAR    *pcbValue)
+    SQLLEN         cbValueMax,
+    SQLLEN FAR    *pcbValue)
 {
 	struct _hstmt *stmt;
 	struct _hdbc *dbc;
@@ -1348,7 +1348,7 @@ SQLRETURN SQL_API SQLParamData(
 SQLRETURN SQL_API SQLPutData(
     SQLHSTMT           hstmt,
     SQLPOINTER         rgbValue,
-    SQLINTEGER         cbValue)
+    SQLLEN         cbValue)
 {
 	TRACE("SQLPutData");
 	return SQL_SUCCESS;
@@ -1357,7 +1357,7 @@ SQLRETURN SQL_API SQLPutData(
 SQLRETURN SQL_API SQLSetConnectOption(
     SQLHDBC            hdbc,
     SQLUSMALLINT       fOption,
-    SQLUINTEGER        vParam)
+    SQLULEN        vParam)
 {
 	TRACE("SQLSetConnectOption");
 	return SQL_SUCCESS;
@@ -1366,7 +1366,7 @@ SQLRETURN SQL_API SQLSetConnectOption(
 SQLRETURN SQL_API SQLSetStmtOption(
     SQLHSTMT           hstmt,
     SQLUSMALLINT       fOption,
-    SQLUINTEGER        vParam)
+    SQLULEN        vParam)
 {
 	TRACE("SQLSetStmtOption");
 	return SQL_SUCCESS;
