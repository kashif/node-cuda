#include "ctx.hpp"
#include "device.hpp"

Persistent<FunctionTemplate> Ctx::constructor_template;

void Ctx::Initialize(Handle<Object> target) {
  HandleScope scope;
  
  Local<FunctionTemplate> t = FunctionTemplate::New(Ctx::New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("Ctx"));

  NODE_SET_PROTOTYPE_METHOD(constructor_template, "Destroy", Ctx::destroy);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "PushCurrent", Ctx::pushCurrent);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "PopCurrent", Ctx::popCurrent);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "SetCurrent", Ctx::setCurrent);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "GetCurrent", Ctx::getCurrent);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "Synchronize", Ctx::synchronize);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "GetApiVersion", Ctx::getApiVersion);

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

Handle<Value> Ctx::destroy(const Arguments& args) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(args.This());

  CUresult error = cuCtxDestroy(pctx->m_context);
  return scope.Close(Number::New(error));
}

Handle<Value> Ctx::pushCurrent(const Arguments& args) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(args.This());

  CUresult error = cuCtxPushCurrent(pctx->m_context);
  return scope.Close(Number::New(error));
}

Handle<Value> Ctx::popCurrent(const Arguments& args) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(args.This());

  CUresult error = cuCtxPopCurrent(&(pctx->m_context));
  return scope.Close(Number::New(error));
}

Handle<Value> Ctx::setCurrent(const Arguments& args) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(args.This());

  CUresult error = cuCtxSetCurrent(pctx->m_context);
  return scope.Close(Number::New(error));
}

Handle<Value> Ctx::getCurrent(const Arguments& args) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(args.This());

  CUresult error = cuCtxGetCurrent(&(pctx->m_context));
  return scope.Close(Number::New(error));
}

Handle<Value> Ctx::synchronize(const Arguments& args) {
  HandleScope scope;

  CUresult error = cuCtxSynchronize();
  return scope.Close(Number::New(error));
}

Handle<Value> Ctx::getApiVersion(const Arguments& args) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(args.This());

  unsigned int version;
  CUresult error = cuCtxGetApiVersion(pctx->m_context, &version);
  
  return scope.Close(Number::New(version));
}
