#include "cuda_mem.hpp"

Persistent<FunctionTemplate> CudaMem::constructor_template;

void CudaMem::Initialize(Handle<Object> target) {
  HandleScope scope;
  
  Local<FunctionTemplate> t = FunctionTemplate::New(CudaMem::New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("CudaMem"));

  NODE_SET_PROTOTYPE_METHOD(constructor_template, "Alloc", CudaMem::alloc);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "AllocPitch", CudaMem::allocPitch);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "Free", CudaMem::free);

  target->Set(String::NewSymbol("CudaMem"), constructor_template->GetFunction());
}

Handle<Value> CudaMem::New(const Arguments& args) {
  HandleScope scope;

  CudaMem *cuptr = new CudaMem();
  cuptr->Wrap(args.Holder());

  return args.This();
}

Handle<Value> CudaMem::alloc(const Arguments& args) {
  HandleScope scope;
  CudaMem *cuptr = ObjectWrap::Unwrap<CudaMem>(args.Holder());

  size_t bytesize = args[0]->Uint32Value();
  CUresult error = cuMemAlloc(&(cuptr->m_devicePtr), bytesize);

  return scope.Close(Number::New(error));
}

Handle<Value> CudaMem::allocPitch(const Arguments& args) {
  HandleScope scope;
  CudaMem *cuptr = ObjectWrap::Unwrap<CudaMem>(args.Holder());

  size_t bytesize = args[0]->Uint32Value();
  size_t pPitch;
  size_t WidthInBytes = args[1]->Uint32Value();
  size_t Height = args[2]->Uint32Value();
  unsigned int ElementSizeBytes = args[2]->Uint32Value();
  CUresult error = cuMemAllocPitch(&(cuptr->m_devicePtr), &pPitch, WidthInBytes, Height, ElementSizeBytes);

  return scope.Close(Number::New(pPitch));
}

Handle<Value> CudaMem::free(const Arguments& args) {
  HandleScope scope;
  CudaMem *cuptr = ObjectWrap::Unwrap<CudaMem>(args.Holder());

  CUresult error = cuMemFree(cuptr->m_devicePtr);

  return scope.Close(Number::New(error));
}