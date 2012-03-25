#include "function.hpp"
#include "mem.hpp"

using namespace NodeCuda;

Persistent<FunctionTemplate> NodeCuda::Function::constructor_template;

void NodeCuda::Function::Initialize(Handle<Object> target) {
  HandleScope scope;
  
  Local<FunctionTemplate> t = FunctionTemplate::New(NodeCuda::Function::New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("CudaFunction"));

  NODE_SET_PROTOTYPE_METHOD(constructor_template, "launch", NodeCuda::Function::LaunchKernel);
  
  // Function objects can only be created by cuModuleGetFunction
}

Handle<Value> NodeCuda::Function::New(const Arguments& args) {
  HandleScope scope;

  NodeCuda::Function *pfunction = new NodeCuda::Function();
  pfunction->Wrap(args.This());

  return args.This();
}

Handle<Value> NodeCuda::Function::LaunchKernel(const Arguments& args) {
  HandleScope scope;
  Function *pfunction = ObjectWrap::Unwrap<Function>(args.This());

  Local<Array> gridDim = Local<Array>::Cast(args[0]);
  unsigned int gridDimX = gridDim->Get(0)->Uint32Value();
  unsigned int gridDimY = gridDim->Get(1)->Uint32Value();
  unsigned int gridDimZ = gridDim->Get(2)->Uint32Value();
  
  Local<Array> blockDim = Local<Array>::Cast(args[1]);
  unsigned int blockDimX = blockDim->Get(0)->Uint32Value();
  unsigned int blockDimY = blockDim->Get(1)->Uint32Value();
  unsigned int blockDimZ = blockDim->Get(2)->Uint32Value();
  
  Mem *mem = ObjectWrap::Unwrap<Mem>(args[2]->ToObject());

  void *cuArgs[] = { &mem->m_devicePtr };

  CUresult error = cuLaunchKernel(pfunction->m_function,
    gridDimX, gridDimY, gridDimZ,
    blockDimX, blockDimY, blockDimZ,
    0, 0, cuArgs, NULL);
  return scope.Close(Number::New(error));
}
