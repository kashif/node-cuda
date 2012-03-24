#include "mem.hpp"

Persistent<FunctionTemplate> Mem::constructor_template;

void Mem::Initialize(Handle<Object> target) {
  HandleScope scope;
  
  Local<FunctionTemplate> t = FunctionTemplate::New(Mem::New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("CudaMem"));

  // Mem objects can only be created by allocation functions
  NODE_SET_METHOD(target, "memAlloc", Mem::Alloc);
  NODE_SET_METHOD(target, "memAllocPitch", Mem::AllocPitch);
  
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "free", Mem::Free);
}

Handle<Value> Mem::New(const Arguments& args) {
  HandleScope scope;

  Mem *pmem = new Mem();
  pmem->Wrap(args.This());

  return args.This();
}

Handle<Value> Mem::Alloc(const Arguments& args) {
  HandleScope scope;
  Local<Object> result = constructor_template->InstanceTemplate()->NewInstance();
  Mem *pmem = ObjectWrap::Unwrap<Mem>(result);

  size_t bytesize = args[0]->Uint32Value();
  CUresult error = cuMemAlloc(&(pmem->m_devicePtr), bytesize);
  
  result->Set(String::New("size"), Integer::NewFromUnsigned(bytesize));
  result->Set(String::New("error"), Integer::New(error));

  return scope.Close(result);
}

Handle<Value> Mem::AllocPitch(const Arguments& args) {
  HandleScope scope;
  Local<Object> result = constructor_template->InstanceTemplate()->NewInstance();
  Mem *pmem = ObjectWrap::Unwrap<Mem>(result);

  size_t pPitch;
  unsigned int ElementSizeBytes = args[2]->Uint32Value();
  size_t WidthInBytes = ElementSizeBytes * args[0]->Uint32Value();
  size_t Height = args[1]->Uint32Value();
  CUresult error = cuMemAllocPitch(&(pmem->m_devicePtr), &pPitch, WidthInBytes, Height, ElementSizeBytes);
  
  result->Set(String::New("size"), Integer::NewFromUnsigned(pPitch * Height));
  result->Set(String::New("pitch"), Integer::NewFromUnsigned(pPitch));
  result->Set(String::New("error"), Integer::New(error));

  return scope.Close(result);
}

Handle<Value> Mem::Free(const Arguments& args) {
  HandleScope scope;
  Mem *pmem = ObjectWrap::Unwrap<Mem>(args.This());

  CUresult error = cuMemFree(pmem->m_devicePtr);

  return scope.Close(Number::New(error));
}
