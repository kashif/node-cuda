#include "module.hpp"

Persistent<FunctionTemplate> Module::constructor_template;

void Module::Initialize(Handle<Object> target) {
  HandleScope scope;
  
  Local<FunctionTemplate> t = FunctionTemplate::New(Module::New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("CudaModule"));

  // Module objects can only be created by load functions
  NODE_SET_METHOD(target, "moduleLoad", Module::Load);
}

Handle<Value> Module::New(const Arguments& args) {
  HandleScope scope;

  Module *pmem = new Module();
  pmem->Wrap(args.This());

  return args.This();
}

Handle<Value> Module::Load(const Arguments& args) {
  HandleScope scope;
  Local<Object> result = constructor_template->InstanceTemplate()->NewInstance();
  Module *pmodule = ObjectWrap::Unwrap<Module>(result);

  String::AsciiValue fname(args[0]);
  CUresult error = cuModuleLoad(&(pmodule->m_module), *fname);
  
  result->Set(String::New("fname"), args[0]);
  result->Set(String::New("error"), Integer::New(error));
  
  return scope.Close(result);
}

