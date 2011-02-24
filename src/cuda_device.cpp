#include "cuda_device.hpp"

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