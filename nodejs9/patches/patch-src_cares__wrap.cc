$NetBSD$

--- src/cares_wrap.cc.orig	2017-05-30 17:32:13.000000000 +0000
+++ src/cares_wrap.cc
@@ -1548,8 +1548,10 @@ void Initialize(Local<Object> target,
               Integer::New(env->isolate(), AF_UNSPEC));
   target->Set(FIXED_ONE_BYTE_STRING(env->isolate(), "AI_ADDRCONFIG"),
               Integer::New(env->isolate(), AI_ADDRCONFIG));
+#if defined(AI_V4MAPPED)
   target->Set(FIXED_ONE_BYTE_STRING(env->isolate(), "AI_V4MAPPED"),
               Integer::New(env->isolate(), AI_V4MAPPED));
+#endif
 
   auto is_construct_call_callback =
       [](const FunctionCallbackInfo<Value>& args) {
