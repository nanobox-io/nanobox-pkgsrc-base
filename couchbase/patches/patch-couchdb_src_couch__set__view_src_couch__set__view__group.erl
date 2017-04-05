$NetBSD$

--- couchdb/src/couch_set_view/src/couch_set_view_group.erl.orig	2017-01-30 21:15:58.000000000 +0000
+++ couchdb/src/couch_set_view/src/couch_set_view_group.erl
@@ -118,7 +118,7 @@
     auto_transfer_replicas = true      :: boolean(),
     replica_partitions = []            :: ordsets:ordset(partition_id()),
     pending_transition_waiters = []    :: [{From::{pid(), reference()}, #set_view_group_req{}}],
-    update_listeners = dict:new()      :: dict(),
+    update_listeners = dict:new()      :: dict:dict(),
     compact_log_files = nil            :: 'nil' | {[[string()]], partition_seqs(), partition_versions()},
     timeout = ?DEFAULT_TIMEOUT         :: non_neg_integer() | 'infinity'
 }).
@@ -3163,7 +3163,7 @@ process_partial_update(State, NewGroup0)
     }.
 
 
--spec notify_update_listeners(#state{}, dict(), #set_view_group{}) -> dict().
+-spec notify_update_listeners(#state{}, dict:dict(), #set_view_group{}) -> dict:dict().
 notify_update_listeners(State, Listeners, NewGroup) ->
     case dict:size(Listeners) == 0 of
     true ->
@@ -3202,7 +3202,7 @@ notify_update_listeners(State, Listeners
     end.
 
 
--spec error_notify_update_listeners(#state{}, dict(), monitor_error()) -> dict().
+-spec error_notify_update_listeners(#state{}, dict:dict(), monitor_error()) -> dict:dict().
 error_notify_update_listeners(State, Listeners, Error) ->
     _ = dict:fold(
         fun(Ref, #up_listener{pid = ListPid, partition = PartId}, _Acc) ->
