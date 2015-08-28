$NetBSD$

--- server/core_filters.c.orig	2015-05-22 13:28:00.000000000 +0000
+++ server/core_filters.c
@@ -643,18 +643,12 @@ static apr_status_t send_brigade_nonbloc
             if ((apr_file_flags_get(fd) & APR_SENDFILE_ENABLED) &&
                 (bucket->length >= AP_MIN_SENDFILE_BYTES)) {
                 if (nvec > 0) {
-                    (void)apr_socket_opt_set(s, APR_TCP_NOPUSH, 1);
                     rv = writev_nonblocking(s, vec, nvec, bb, bytes_written, c);
                     if (rv != APR_SUCCESS) {
-                        (void)apr_socket_opt_set(s, APR_TCP_NOPUSH, 0);
                         return rv;
                     }
                 }
                 rv = sendfile_nonblocking(s, bucket, bytes_written, c);
-                if (nvec > 0) {
-                    (void)apr_socket_opt_set(s, APR_TCP_NOPUSH, 0);
-                    nvec = 0;
-                }
                 if (rv != APR_SUCCESS) {
                     return rv;
                 }
