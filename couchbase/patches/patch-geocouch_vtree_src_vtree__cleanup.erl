$NetBSD$

--- geocouch/vtree/src/vtree_cleanup.erl.orig	2017-01-30 21:15:58.000000000 +0000
+++ geocouch/vtree/src/vtree_cleanup.erl
@@ -29,7 +29,7 @@ cleanup(Vt, []) ->
 cleanup(#vtree{root=nil}=Vt, _Nodes) ->
     Vt;
 cleanup(Vt, Nodes) ->
-    T1 = now(),
+    T1 = erlang:timestamp(),
     Root = Vt#vtree.root,
     PartitionedNodes = [Nodes],
     KpNodes = cleanup_multiple(Vt, PartitionedNodes, [Root]),
@@ -39,7 +39,7 @@ cleanup(Vt, Nodes) ->
                       vtree_modify:write_new_root(Vt, KpNodes)
               end,
     ?LOG_DEBUG("Cleanup took: ~ps~n",
-               [timer:now_diff(now(), T1)/1000000]),
+               [timer:now_diff(erlang:timestamp(), T1)/1000000]),
     Vt#vtree{root=NewRoot}.
 
 -spec cleanup_multiple(Vt :: #vtree{}, ToCleanup :: [#kv_node{}],
