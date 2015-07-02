$NetBSD$

--- scripts/wsrep_sst_rsync.sh.orig	2015-05-12 21:42:37.000000000 +0000
+++ scripts/wsrep_sst_rsync.sh
@@ -57,23 +57,20 @@ check_pid_and_port()
     local rsync_pid=$2
     local rsync_port=$3
 
-    if ! which lsof > /dev/null; then
-      wsrep_log_error "lsof tool not found in PATH! Make sure you have it installed."
-      exit 2 # ENOENT
+    if [ "$OS" == "Darwin" -o "$OS" == "FreeBSD" ]; then
+        # no netstat --program(-p) option in Darwin and FreeBSD
+        check_pid $pid_file && \
+        lsof -i -Pn 2>/dev/null | \
+        grep "(LISTEN)" | grep ":$rsync_port" | grep -w '^rsync[[:space:]]\+'"$rsync_pid" >/dev/null
+    elif [ "$OS" == "SunOS" ]; then
+        check_pid $pid_file && \
+        netstat -an 2>/dev/null | \
+        grep LISTEN | grep \.$rsync_port > /dev/null
+    else
+        check_pid $pid_file && \
+        netstat -lnpt 2>/dev/null | \
+        grep LISTEN | grep \:$rsync_port | grep $rsync_pid/rsync >/dev/null
     fi
-
-    local port_info=$(lsof -i :$rsync_port -Pn 2>/dev/null | \
-        grep "(LISTEN)")
-    local is_rsync=$(echo $port_info | \
-        grep -w '^rsync[[:space:]]\+'"$rsync_pid" 2>/dev/null)
-
-    if [ -n "$port_info" -a -z "$is_rsync" ]; then
-        wsrep_log_error "rsync daemon port '$rsync_port' has been taken"
-        exit 16 # EBUSY
-    fi
-    check_pid $pid_file && \
-        [ -n "$port_info" ] && [ -n "$is_rsync" ] && \
-        [ $(cat $pid_file) -eq $rsync_pid ]
 }
 
 MAGIC_FILE="$WSREP_SST_OPT_DATA/rsync_sst_complete"
