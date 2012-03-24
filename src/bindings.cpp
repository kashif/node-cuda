#include "bindings.hpp"
#include "ctx.hpp"
#include "device.hpp"
#include "function.hpp"
#include "mem.hpp"
#include "module.hpp"

using namespace NodeCuda;

void init (Handle<Object> target) {
  HandleScope scope;

  // Initiailze the cuda driver api
  cuInit(0);

  // These methods don't need instances
  target->SetAccessor(String::New("driverVersion"), GetDriverVersion);
  target->SetAccessor(String::New("deviceCount"), GetDeviceCount);

  // Initialize driver api bindings
  Ctx::Initialize(target);
  Device::Initialize(target);
  NodeCuda::Function::Initialize(target);
  Mem::Initialize(target);
  Module::Initialize(target);
}

Handle<Value> NodeCuda::GetDriverVersion(Local<String> property, const AccessorInfo &info) {
  HandleScope scope;
  int driverVersion = 0;
  cuDriverGetVersion(&driverVersion);
  return scope.Close(Integer::New(driverVersion));
}

Handle<Value> NodeCuda::GetDeviceCount(Local<String> property, const AccessorInfo &info) {
  HandleScope scope;
  int count = 0;
  cuDeviceGetCount(&count);
  return scope.Close(Integer::New(count));
}

NODE_MODULE(cuda, init);
