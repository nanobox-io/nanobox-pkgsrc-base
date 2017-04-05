$NetBSD$

--- geocouch/vtree/src/vtree_insert.erl.orig	2017-01-30 21:15:58.000000000 +0000
+++ geocouch/vtree/src/vtree_insert.erl
@@ -26,7 +26,7 @@
 insert(Vt, []) ->
     Vt;
 insert(#vtree{root=nil}=Vt, Nodes) ->
-    T1 = now(),
+    T1 = erlang:timestamp(),
     % If we would do single inserts, the first node that was inserted would
     % have set the original Mbb `MbbO`
     MbbO = (hd(Nodes))#kv_node.key,
@@ -48,7 +48,7 @@ insert(#vtree{root=nil}=Vt, Nodes) ->
             ArbitraryBulkSize = round(math:log(Threshold)+50),
             Vt3 = insert_in_bulks(Vt2, Rest, ArbitraryBulkSize),
             ?LOG_DEBUG("Insertion into empty tree took: ~ps~n",
-                      [timer:now_diff(now(), T1)/1000000]),
+                      [timer:now_diff(erlang:timestamp(), T1)/1000000]),
             ?LOG_DEBUG("Root pos: ~p~n", [(Vt3#vtree.root)#kp_node.childpointer]),
             Vt3;
         false ->
@@ -56,13 +56,13 @@ insert(#vtree{root=nil}=Vt, Nodes) ->
             Vt#vtree{root=Root}
     end;
 insert(Vt, Nodes) ->
-    T1 = now(),
+    T1 = erlang:timestamp(),
     Root = Vt#vtree.root,
     PartitionedNodes = [Nodes],
     KpNodes = insert_multiple(Vt, PartitionedNodes, [Root]),
     NewRoot = vtree_modify:write_new_root(Vt, KpNodes),
     ?LOG_DEBUG("Insertion into existing tree took: ~ps~n",
-               [timer:now_diff(now(), T1)/1000000]),
+               [timer:now_diff(erlang:timestamp(), T1)/1000000]),
     Vt#vtree{root=NewRoot}.
 
 
