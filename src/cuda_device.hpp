#ifndef CUDA_DEVICE_HPP
#define CUDA_DEVICE_HPP

#include <cuda.h>
#include "bindings.hpp"

class CudaDevice : public EventEmitter {
public:
  static void Initialize (Handle<Object> target) {
    HandleScope scope;

    cuInit(0);

    NODE_SET_METHOD(target, "DriverGetVersion", driverGetVersion);
    NODE_SET_METHOD(target, "DeviceGetCount", deviceGetCount);
  }

protected:
  CUdevice m_device;

  static v8::Handle<v8::Value> driverGetVersion(const v8::Arguments& args);
  static v8::Handle<v8::Value> deviceGetCount(const v8::Arguments& args);

  CudaDevice() : EventEmitter () {
    m_device = NULL;
  }
  ~CudaDevice();
};

#endif