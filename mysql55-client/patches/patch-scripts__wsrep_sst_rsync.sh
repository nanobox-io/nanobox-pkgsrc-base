$NetBSD$

--- scripts/wsrep_sst_rsync.sh.orig	2015-04-24 19:37:26.633490045 +0000
+++ scripts/wsrep_sst_rsync.sh
@@ -56,12 +56,18 @@ check_pid_and_port()
     local pid_file=$1
     local rsync_pid=$2
     local rsync_port=$3
-
-    local port_info=$(lsof -i :$rsync_port -Pn 2>/dev/null | \
-        grep "(LISTEN)")
-    local is_rsync=$(echo $port_info | \
-        grep -w '^rsync[[:space:]]\+'"$rsync_pid" 2>/dev/null)
-
+    local port_info=
+    local is_rsync=
+    if [ "$OS" == "SunOS" ]; then
+        port_info=$(lsof -o $rsync_port | grep $rsync_pid)
+        is_rsync=$(echo $port_info |
+            grep -w '^'"$rsync_pid"'[[:space:]]\+rsync')
+    else
+        port_info=$(lsof -i :$rsync_port -Pn 2>/dev/null | \
+            grep "(LISTEN)")
+        is_rsync=$(echo $port_info | \
+            grep -w '^rsync[[:space:]]\+'"$rsync_pid" 2>/dev/null)
+    fi
     if [ -n "$port_info" -a -z "$is_rsync" ]; then
         wsrep_log_error "rsync daemon port '$rsync_port' has been taken"
         exit 16 # EBUSY
