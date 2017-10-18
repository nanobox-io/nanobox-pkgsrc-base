$NetBSD$

--- src/cluster.c.orig	2015-04-01 14:01:44.000000000 +0000
+++ src/cluster.c
@@ -42,6 +42,46 @@
 #include <sys/file.h>
 #include <math.h>
 
+#ifdef __sun
+#include <fcntl.h>
+#define   LOCK_SH   1    /* shared lock */
+#define   LOCK_EX   2    /* exclusive lock */
+#define   LOCK_NB   4    /* don't block when locking */
+#define   LOCK_UN   8    /* unlock */
+
+int flock(int fd, int op) {
+	int rc = 0;
+
+	struct flock fl = {0};
+
+	switch (op & (LOCK_EX|LOCK_SH|LOCK_UN)) {
+	case LOCK_EX:
+		fl.l_type = F_WRLCK;
+		break;
+
+	case LOCK_SH:
+		fl.l_type = F_RDLCK;
+		break;
+
+	case LOCK_UN:
+		fl.l_type = F_UNLCK;
+		break;
+
+	default:
+		errno = EINVAL;
+		return -1;
+	}
+
+	fl.l_whence = SEEK_SET;
+	rc = fcntl(fd, op & LOCK_NB ? F_SETLK : F_SETLKW, &fl);
+
+	if (rc && (errno == EAGAIN))
+		errno = EWOULDBLOCK;
+
+	return rc;
+}
+#endif
+
 /* A global reference to myself is handy to make code more clear.
  * Myself always points to server.cluster->myself, that is, the clusterNode
  * that represents this node. */
