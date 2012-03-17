#include "cuda_device.hpp"

Persistent<FunctionTemplate> CudaDevice::constructor_template;

void CudaDevice::Initialize (Handle<Object> target) {
  HandleScope scope;

  cuInit(0);

  NODE_SET_METHOD(target, "DriverGetVersion", driverGetVersion);
  NODE_SET_METHOD(target, "DeviceGetCount", deviceGetCount);

  Local<FunctionTemplate> t = FunctionTemplate::New(CudaDevice::New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("CudaDevice"));

  NODE_SET_PROTOTYPE_METHOD(constructor_template, "GetName", CudaDevice::getName);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "TotalMem", CudaDevice::totalMem);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "ComputeCapability", CudaDevice::computeCapability);

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

  int ordinal = args[0]->IntegerValue();
  CudaDevice *cu = new CudaDevice();
  cuDeviceGet(&(cu->m_device), ordinal);

  cu->Wrap(args.This());
  return args.This();
}

Handle<Value> CudaDevice::getName(const Arguments& args) {
  HandleScope scope;

  CudaDevice *cu = ObjectWrap::Unwrap<CudaDevice>(args.This());
  char deviceName[256];
  cuDeviceGetName(deviceName, 256, cu->m_device);

  Local<String> result = String::New(deviceName);
  return scope.Close(result);
}

Handle<Value> CudaDevice::computeCapability(const Arguments& args) {
  HandleScope scope;

  CudaDevice *cu = ObjectWrap::Unwrap<CudaDevice>(args.This());
  int major = 0, minor = 0;
  cuDeviceComputeCapability(&major, &minor, cu->m_device);
  
  Local<Array> result = Array::New(2);
  result->Set(0, Integer::New(major));
  result->Set(1, Integer::New(minor));
  return scope.Close(result);
}

Handle<Value> CudaDevice::totalMem(const Arguments& args) {
  HandleScope scope;

  CudaDevice *cu = ObjectWrap::Unwrap<CudaDevice>(args.This());
  size_t totalGlobalMem;
  cuDeviceTotalMem(&totalGlobalMem, cu->m_device);
  
  return scope.Close(Number::New(totalGlobalMem));
}