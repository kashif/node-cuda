#include "cuda_device.hpp"

Persistent<FunctionTemplate> CudaDevice::constructor_template;

void CudaDevice::Initialize (Handle<Object> target) {
  HandleScope scope;

  Local<FunctionTemplate> t = FunctionTemplate::New(CudaDevice::New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("CudaDevice"));

  cuInit(0);

  NODE_SET_METHOD(target, "DriverGetVersion", driverGetVersion);
  NODE_SET_METHOD(target, "DeviceGetCount", deviceGetCount);

  target->Set(String::NewSymbol("CudaDevice"), constructor_template->GetFunction());
}

Handle<Value> CudaDevice::driverGetVersion(const Arguments& args) {
  HandleScope scope;
  int driverVersion = 0;
  cuDriverGetVersion(&driverVersion);
  return scope.Close(Integer::New(driverVersion));
}

Handle<Value> CudaDevice::deviceGetCount(const Arguments& args) {
  HandleScope scope;
  int count = 0;
  cuDeviceGetCount(&count);
  return scope.Close(Integer::New(count));
}

Handle<Value> CudaDevice::New(const Arguments& args) {
  HandleScope scope;
  CudaDevice *cu = new CudaDevice();
  cu->Wrap(args.This());
  return args.This();
}