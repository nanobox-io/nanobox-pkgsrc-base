$NetBSD$

--- geocouch/gc-couchbase/src/spatial_view.erl.orig	2017-01-30 21:15:58.000000000 +0000
+++ geocouch/gc-couchbase/src/spatial_view.erl
@@ -201,7 +201,7 @@ decode_key_docid(<<NumDoubles:16, Rest/b
 
 
 % Build the tree out of the sorted files
--spec finish_build(#set_view_group{}, dict(), string()) ->
+-spec finish_build(#set_view_group{}, dict:dict(), string()) ->
                           {#set_view_group{}, pid()}.
 finish_build(Group, TmpFiles, TmpDir) ->
     #set_view_group{
