$NetBSD$

--- src/libs/zbxsysinfo/common/net.c.orig	2018-02-16 08:39:10.000000000 +0000
+++ src/libs/zbxsysinfo/common/net.c
@@ -240,6 +240,7 @@ static int	dns_query(AGENT_REQUEST *requ
 	struct servent	*s;
 	HEADER		*hp;
 	struct protoent	*pr;
+	struct __res_state	res_state;
 #if PACKETSZ > 1024
 	unsigned char	buf[PACKETSZ];
 #else
