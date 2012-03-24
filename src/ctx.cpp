#include "ctx.hpp"
#include "device.hpp"

Persistent<FunctionTemplate> Ctx::constructor_template;

void Ctx::Initialize(Handle<Object> target) {
  HandleScope scope;
  
  Local<FunctionTemplate> t = FunctionTemplate::New(Ctx::New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("CudaCtx"));

  NODE_SET_PROTOTYPE_METHOD(constructor_template, "destroy", Ctx::Destroy);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "pushCurrent", Ctx::PushCurrent);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "popCurrent", Ctx::PopCurrent);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "setCurrent", Ctx::SetCurrent);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "getCurrent", Ctx::GetCurrent);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "synchronize", Ctx::Synchronize);
  constructor_template->InstanceTemplate()->SetAccessor(String::New("apiVersion"), Ctx::GetApiVersion);

  target->Set(String::NewSymbol("Ctx"), constructor_template->GetFunction());
}

Handle<Value> Ctx::New(const Arguments& args) {
  HandleScope scope;
  
  Ctx *pctx = new Ctx();
  pctx->Wrap(args.This());
  
  unsigned int flags = args[0]->Uint32Value();
  Device *pdev = ObjectWrap::Unwrap<Device>(args[1]->ToObject());
  
  CUresult error = cuCtxCreate(&(pctx->m_context), flags, pdev->m_device);
  return args.This();
}

Handle<Value> Ctx::Destroy(const Arguments& args) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(args.This());

  CUresult error = cuCtxDestroy(pctx->m_context);
  return scope.Close(Number::New(error));
}

Handle<Value> Ctx::PushCurrent(const Arguments& args) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(args.This());

  CUresult error = cuCtxPushCurrent(pctx->m_context);
  return scope.Close(Number::New(error));
}

Handle<Value> Ctx::PopCurrent(const Arguments& args) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(args.This());

  CUresult error = cuCtxPopCurrent(&(pctx->m_context));
  return scope.Close(Number::New(error));
}

Handle<Value> Ctx::SetCurrent(const Arguments& args) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(args.This());

  CUresult error = cuCtxSetCurrent(pctx->m_context);
  return scope.Close(Number::New(error));
}

Handle<Value> Ctx::GetCurrent(const Arguments& args) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(args.This());

  CUresult error = cuCtxGetCurrent(&(pctx->m_context));
  return scope.Close(Number::New(error));
}

Handle<Value> Ctx::Synchronize(const Arguments& args) {
  HandleScope scope;

  CUresult error = cuCtxSynchronize();
  return scope.Close(Number::New(error));
}

Handle<Value> Ctx::GetApiVersion(Local<String> property, const AccessorInfo &info) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(info.Holder());

  unsigned int version;
  CUresult error = cuCtxGetApiVersion(pctx->m_context, &version);
  
  return scope.Close(Number::New(version));
}
