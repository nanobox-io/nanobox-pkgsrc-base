$NetBSD$

--- couchdb/src/couch_dcp/src/couch_dcp_client.erl.orig	2017-01-30 21:15:58.000000000 +0000
+++ couchdb/src/couch_dcp/src/couch_dcp_client.erl
@@ -47,13 +47,13 @@
     bufsocket = nil                 :: #bufsocket{} | nil,
     timeout = 5000                  :: timeout(),
     request_id = 0                  :: request_id(),
-    pending_requests = dict:new()   :: dict(),
-    stream_queues = dict:new()      :: dict(),
+    pending_requests = dict:new()   :: dict:dict(),
+    stream_queues = dict:new()      :: dict:dict(),
     active_streams = []             :: list(),
     worker_pid                      :: pid(),
     max_buffer_size = ?MAX_BUF_SIZE :: integer(),
     total_buffer_size = 0           :: non_neg_integer(),
-    stream_info = dict:new()        :: dict(),
+    stream_info = dict:new()        :: dict:dict(),
     args = []                       :: list()
 }).
 
@@ -1378,7 +1378,7 @@ set_buffer_size(State, Size) ->
         {error, Error}
     end.
 
--spec get_queue_size(queue(), non_neg_integer()) -> non_neg_integer().
+-spec get_queue_size(queue:queue(), non_neg_integer()) -> non_neg_integer().
 get_queue_size(EvQueue, Size) ->
     case queue:out(EvQueue) of
     {empty, _} ->
