#include "module.hpp"
#include "function.hpp"

using namespace NodeCuda;

Persistent<FunctionTemplate> Module::constructor_template;

void Module::Initialize(Handle<Object> target) {
  HandleScope scope;
  
  Local<FunctionTemplate> t = FunctionTemplate::New(Module::New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("CudaModule"));

  // Module objects can only be created by load functions
  NODE_SET_METHOD(target, "moduleLoad", Module::Load);
  
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "getFunction", Module::GetFunction);
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

Handle<Value> Module::GetFunction(const Arguments& args) {
  HandleScope scope;
  Local<Object> result = NodeCuda::Function::constructor_template->InstanceTemplate()->NewInstance();
  Module *pmodule = ObjectWrap::Unwrap<Module>(args.This());
  NodeCuda::Function *pfunction = ObjectWrap::Unwrap<NodeCuda::Function>(result);

  String::AsciiValue name(args[0]);
  CUresult error = cuModuleGetFunction(&(pfunction->m_function), pmodule->m_module, *name);
  
  result->Set(String::New("name"), args[0]);
  result->Set(String::New("error"), Integer::New(error));
  
  return scope.Close(result);
}

