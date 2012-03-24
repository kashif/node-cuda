#include "mem.hpp"

Persistent<FunctionTemplate> Mem::constructor_template;

void Mem::Initialize(Handle<Object> target) {
  HandleScope scope;
  
  Local<FunctionTemplate> t = FunctionTemplate::New(Mem::New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("Mem"));

  NODE_SET_PROTOTYPE_METHOD(constructor_template, "Alloc", Mem::alloc);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "AllocPitch", Mem::allocPitch);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "Free", Mem::free);

  target->Set(String::NewSymbol("Mem"), constructor_template->GetFunction());
}

Handle<Value> Mem::New(const Arguments& args) {
  HandleScope scope;

  Mem *cuptr = new Mem();
  cuptr->Wrap(args.This());

  return args.This();
}

Handle<Value> Mem::alloc(const Arguments& args) {
  HandleScope scope;
  Mem *cuptr = ObjectWrap::Unwrap<Mem>(args.This());

  size_t bytesize = args[0]->Uint32Value();
  CUresult error = cuMemAlloc(&(cuptr->m_devicePtr), bytesize);

  return scope.Close(Number::New(error));
}

Handle<Value> Mem::allocPitch(const Arguments& args) {
  HandleScope scope;
  Mem *cuptr = ObjectWrap::Unwrap<Mem>(args.This());

  size_t bytesize = args[0]->Uint32Value();
  size_t pPitch;
  size_t WidthInBytes = args[1]->Uint32Value();
  size_t Height = args[2]->Uint32Value();
  unsigned int ElementSizeBytes = args[2]->Uint32Value();
  CUresult error = cuMemAllocPitch(&(cuptr->m_devicePtr), &pPitch, WidthInBytes, Height, ElementSizeBytes);

  return scope.Close(Number::New(pPitch));
}

Handle<Value> Mem::free(const Arguments& args) {
  HandleScope scope;
  Mem *cuptr = ObjectWrap::Unwrap<Mem>(args.This());

  CUresult error = cuMemFree(cuptr->m_devicePtr);

  return scope.Close(Number::New(error));
}
