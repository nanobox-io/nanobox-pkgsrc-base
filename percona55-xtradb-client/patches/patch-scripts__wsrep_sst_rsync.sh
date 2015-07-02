$NetBSD$

--- scripts/wsrep_sst_rsync.sh.orig	2014-05-08 00:58:25.000000000 +0000
+++ scripts/wsrep_sst_rsync.sh
@@ -55,23 +55,20 @@ check_pid_and_port()
     local rsync_pid=$2
     local rsync_port=$3
 
-    if [[ ! -x `which lsof` ]];then 
-        wsrep_log_error "lsof not found in path: $PATH"
-        exit 2 
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
