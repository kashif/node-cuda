#ifndef CUDA_DEVICE_HPP
#define CUDA_DEVICE_HPP

#include <cuda.h>
#include "bindings.hpp"

class CudaDevice : public EventEmitter {
public:
  static void Initialize (Handle<Object> target);
  
  CUdevice m_device;
protected:
  static Persistent<FunctionTemplate> constructor_template;

  static Handle<Value> New(const Arguments& args);
  static Handle<Value> driverGetVersion(const Arguments& args);
  static Handle<Value> deviceGetCount(const Arguments& args);
  static Handle<Value> getName(const Arguments& args);
  static Handle<Value> computeCapability(const Arguments& args);
  static Handle<Value> totalMem(const Arguments& args);

  CudaDevice() : EventEmitter () {
    m_device = NULL;
  }

  ~CudaDevice(){
  }
};

#endif