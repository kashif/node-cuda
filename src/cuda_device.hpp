#ifndef CUDA_DEVICE_HPP
#define CUDA_DEVICE_HPP

#include <cuda.h>
#include "bindings.hpp"

class CudaDevice : public ObjectWrap {
public:
  static void Initialize(Handle<Object> target);

protected:
  static Persistent<FunctionTemplate> constructor_template;

  static Handle<Value> New(const Arguments& args);
  static Handle<Value> getName(const Arguments& args);
  static Handle<Value> computeCapability(const Arguments& args);
  static Handle<Value> totalMem(const Arguments& args);

  CudaDevice() : ObjectWrap(), m_device(NULL) {}

  ~CudaDevice() {}

private:
  CUdevice m_device;

  friend class CudaCtx;
};

#endif
