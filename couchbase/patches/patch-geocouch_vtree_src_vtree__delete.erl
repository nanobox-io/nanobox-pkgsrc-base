$NetBSD$

--- geocouch/vtree/src/vtree_delete.erl.orig	2017-01-30 21:15:58.000000000 +0000
+++ geocouch/vtree/src/vtree_delete.erl
@@ -30,7 +30,7 @@ delete(Vt, []) ->
 delete(#vtree{root=nil}=Vt, _Nodes) ->
     Vt;
 delete(Vt, Nodes) ->
-    T1 = now(),
+    T1 = erlang:timestamp(),
     Root = Vt#vtree.root,
     PartitionedNodes = [Nodes],
     KpNodes = delete_multiple(Vt, PartitionedNodes, [Root]),
@@ -40,7 +40,7 @@ delete(Vt, Nodes) ->
                       vtree_modify:write_new_root(Vt, KpNodes)
               end,
     ?LOG_DEBUG("Deletion took: ~ps~n",
-               [timer:now_diff(now(), T1)/1000000]),
+               [timer:now_diff(erlang:timestamp(), T1)/1000000]),
     Vt#vtree{root=NewRoot}.
 
 
