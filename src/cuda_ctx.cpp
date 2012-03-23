#include "cuda_ctx.hpp"
#include "cuda_device.hpp"

Persistent<FunctionTemplate> CudaCtx::constructor_template;

void CudaCtx::Initialize(Handle<Object> target) {
  HandleScope scope;
  
  Local<FunctionTemplate> t = FunctionTemplate::New(CudaCtx::New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("CudaCtx"));

  NODE_SET_PROTOTYPE_METHOD(constructor_template, "Destroy", CudaCtx::destroy);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "PushCurrent", CudaCtx::pushCurrent);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "PopCurrent", CudaCtx::popCurrent);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "SetCurrent", CudaCtx::setCurrent);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "GetCurrent", CudaCtx::getCurrent);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "Synchronize", CudaCtx::synchronize);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "GetApiVersion", CudaCtx::getApiVersion);

  target->Set(String::NewSymbol("CudaCtx"), constructor_template->GetFunction());
}

Handle<Value> CudaCtx::New(const Arguments& args) {
  HandleScope scope;
  
  CudaCtx *pctx = new CudaCtx();
  pctx->Wrap(args.This());
  
  unsigned int flags = args[0]->Uint32Value();
  CudaDevice *pdev = ObjectWrap::Unwrap<CudaDevice>(args[1]->ToObject());
  
  CUresult error = cuCtxCreate(&(pctx->m_context), flags, pdev->m_device);
  return args.This();
}

Handle<Value> CudaCtx::destroy(const Arguments& args) {
  HandleScope scope;
  CudaCtx *pctx = ObjectWrap::Unwrap<CudaCtx>(args.This());

  CUresult error = cuCtxDestroy(pctx->m_context);
  return scope.Close(Number::New(error));
}

Handle<Value> CudaCtx::pushCurrent(const Arguments& args) {
  HandleScope scope;
  CudaCtx *pctx = ObjectWrap::Unwrap<CudaCtx>(args.This());

  CUresult error = cuCtxPushCurrent(pctx->m_context);
  return scope.Close(Number::New(error));
}

Handle<Value> CudaCtx::popCurrent(const Arguments& args) {
  HandleScope scope;
  CudaCtx *pctx = ObjectWrap::Unwrap<CudaCtx>(args.This());

  CUresult error = cuCtxPopCurrent(&(pctx->m_context));
  return scope.Close(Number::New(error));
}

Handle<Value> CudaCtx::setCurrent(const Arguments& args) {
  HandleScope scope;
  CudaCtx *pctx = ObjectWrap::Unwrap<CudaCtx>(args.This());

  CUresult error = cuCtxSetCurrent(pctx->m_context);
  return scope.Close(Number::New(error));
}

Handle<Value> CudaCtx::getCurrent(const Arguments& args) {
  HandleScope scope;
  CudaCtx *pctx = ObjectWrap::Unwrap<CudaCtx>(args.This());

  CUresult error = cuCtxGetCurrent(&(pctx->m_context));
  return scope.Close(Number::New(error));
}

Handle<Value> CudaCtx::synchronize(const Arguments& args) {
  HandleScope scope;

  CUresult error = cuCtxSynchronize();
  return scope.Close(Number::New(error));
}

Handle<Value> CudaCtx::getApiVersion(const Arguments& args) {
  HandleScope scope;
  CudaCtx *pctx = ObjectWrap::Unwrap<CudaCtx>(args.This());

  unsigned int version;
  CUresult error = cuCtxGetApiVersion(pctx->m_context, &version);
  
  return scope.Close(Number::New(version));
}
