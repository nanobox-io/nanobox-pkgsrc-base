$NetBSD$

--- couchdb/src/couch_set_view/src/mapreduce_view.erl.orig	2017-01-30 21:15:58.000000000 +0000
+++ couchdb/src/couch_set_view/src/mapreduce_view.erl
@@ -109,7 +109,7 @@ convert_primary_index_kvs_to_binary([{{K
     convert_primary_index_kvs_to_binary(Rest, Group, [{KeyBin, V} | Acc]).
 
 
--spec finish_build(#set_view_group{}, dict(), string()) ->
+-spec finish_build(#set_view_group{}, dict:dict(), string()) ->
                           {#set_view_group{}, pid()}.
 finish_build(Group, TmpFiles, TmpDir) ->
     #set_view_group{
