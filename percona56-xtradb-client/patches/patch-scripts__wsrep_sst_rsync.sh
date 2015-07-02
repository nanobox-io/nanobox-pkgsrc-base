$NetBSD$

--- scripts/wsrep_sst_rsync.sh.orig	2015-03-09 09:28:18.000000000 +0000
+++ scripts/wsrep_sst_rsync.sh
@@ -57,18 +57,24 @@ check_pid_and_port()
     local rsync_pid=$2
     local rsync_port=$3
 
-    local port_info=$(lsof -i :$rsync_port -Pn 2>/dev/null | \
-        grep "(LISTEN)")
-    local is_rsync=$(echo $port_info | \
-        grep -w '^rsync[[:space:]]\+'"$rsync_pid" 2>/dev/null)
+    if [ "$OS" == "SunOS" ]; then
+        check_pid $pid_file && \
+        netstat -an 2>/dev/null | \
+        grep LISTEN | grep \.$rsync_port > /dev/null
+    else
+        local port_info=$(lsof -i :$rsync_port -Pn 2>/dev/null | \
+            grep "(LISTEN)")
+        local is_rsync=$(echo $port_info | \
+            grep -w '^rsync[[:space:]]\+'"$rsync_pid" 2>/dev/null)
 
-    if [ -n "$port_info" -a -z "$is_rsync" ]; then
-        wsrep_log_error "rsync daemon port '$rsync_port' has been taken"
-        exit 16 # EBUSY
+        if [ -n "$port_info" -a -z "$is_rsync" ]; then
+            wsrep_log_error "rsync daemon port '$rsync_port' has been taken"
+            exit 16 # EBUSY
+        fi
+        check_pid $pid_file && \
+            [ -n "$port_info" ] && [ -n "$is_rsync" ] && \
+            [ $(cat $pid_file) -eq $rsync_pid ]
     fi
-    check_pid $pid_file && \
-        [ -n "$port_info" ] && [ -n "$is_rsync" ] && \
-        [ $(cat $pid_file) -eq $rsync_pid ]
 }
 
 MAGIC_FILE="$WSREP_SST_OPT_DATA/rsync_sst_complete"
