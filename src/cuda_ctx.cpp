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

  target->Set(String::NewSymbol("CudaCtx"), constructor_template->GetFunction());
}

Handle<Value> CudaCtx::New(const Arguments& args) {
  HandleScope scope;
  
  CudaCtx *pctx = new CudaCtx();
  pctx->Wrap(args.Holder());
  
  unsigned int flags = args[0]->Uint32Value();
  CudaDevice *pdev = ObjectWrap::Unwrap<CudaDevice>(args[1]->ToObject());
  
  CUresult error = cuCtxCreate(&(pctx->m_context), flags, pdev->m_device);
  return args.This();
}

Handle<Value> CudaCtx::destroy(const Arguments& args) {
  HandleScope scope;
  CudaCtx *pctx = ObjectWrap::Unwrap<CudaCtx>(args.Holder());

  CUresult error = cuCtxDestroy(pctx->m_context);
  return scope.Close(Number::New(error));
}