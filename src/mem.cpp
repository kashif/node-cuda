#include <cstring>
#include <node_buffer.h>
#include "mem.hpp"

using namespace NodeCuda;

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
  
  constructor_template->InstanceTemplate()->SetAccessor(String::New("devicePtr"), Mem::GetDevicePtr);

  NODE_SET_PROTOTYPE_METHOD(constructor_template, "free", Mem::Free);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "copyHtoD", Mem::CopyHtoD);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "copyDtoH", Mem::CopyDtoH);
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

Handle<Value> Mem::CopyHtoD(const Arguments& args) {
  HandleScope scope;
  Mem *pmem = ObjectWrap::Unwrap<Mem>(args.This());

  Local<Object> buf = args[0]->ToObject();
  char *phost = Buffer::Data(buf);
  size_t bytes = Buffer::Length(buf);

  bool async = args.Length() >= 2 && args[1]->IsTrue();

  CUresult error;
  if (async) {
    error = cuMemcpyHtoDAsync(pmem->m_devicePtr, phost, bytes, 0);
  } else {
    error = cuMemcpyHtoD(pmem->m_devicePtr, phost, bytes);
  }

  return scope.Close(Number::New(error));
}

Handle<Value> Mem::CopyDtoH(const Arguments& args) {
  HandleScope scope;
  Mem *pmem = ObjectWrap::Unwrap<Mem>(args.This());

  Local<Object> buf = args[0]->ToObject();
  char *phost = Buffer::Data(buf);
  size_t bytes = Buffer::Length(buf);

  bool async = args.Length() >= 2 && args[1]->IsTrue();

  CUresult error;
  if (async) {
    error = cuMemcpyDtoHAsync(phost, pmem->m_devicePtr, bytes, 0);
  } else {
    error = cuMemcpyDtoH(phost, pmem->m_devicePtr, bytes);
  }

  return scope.Close(Number::New(error));
}

Handle<Value> Mem::GetDevicePtr(Local<String> property, const AccessorInfo &info) {
  HandleScope scope;
  Mem *pmem = ObjectWrap::Unwrap<Mem>(info.Holder());
  Buffer *ptrbuf = Buffer::New(sizeof(pmem->m_devicePtr));

  memcpy(Buffer::Data(ptrbuf->handle_), &pmem->m_devicePtr, sizeof(pmem->m_devicePtr));

  return scope.Close(ptrbuf->handle_);
}
