#include "bindings.hpp"
#include "device.hpp"
#include "ctx.hpp"
#include "mem.hpp"

void init (Handle<Object> target) {
  HandleScope scope;
  
  // Initiailze the cuda driver api
  cuInit(0);

  // These methods don't need instances
  NODE_SET_METHOD(target, "DriverGetVersion", driverGetVersion);
  NODE_SET_METHOD(target, "DeviceGetCount", deviceGetCount);

  // Initialize driver api bindings
  Device::Initialize(target);
  Ctx::Initialize(target);
  Mem::Initialize(target);
}

Handle<Value> driverGetVersion(const Arguments& args) {
  HandleScope scope;
  int driverVersion = 0;
  cuDriverGetVersion(&driverVersion);
  return scope.Close(Integer::New(driverVersion));
}

Handle<Value> deviceGetCount(const Arguments& args) {
  HandleScope scope;
  int count = 0;
  cuDeviceGetCount(&count);
  return scope.Close(Integer::New(count));
}

NODE_MODULE(cuda, init);
