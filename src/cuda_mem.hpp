#ifndef CUDA_MEM_HPP
#define CUDA_MEM_HPP

#include <cuda.h>
#include "bindings.hpp"

class CudaMem : public ObjectWrap {
public:
  static void Initialize(Handle<Object> target);

protected:
  static Persistent<FunctionTemplate> constructor_template;
  
  static Handle<Value> New(const Arguments& args);
  static Handle<Value> alloc(const Arguments& args);
  static Handle<Value> allocPitch(const Arguments& args);
  static Handle<Value> free(const Arguments& args);

  CudaMem() : ObjectWrap(), m_devicePtr(0) {}
  
  ~CudaMem() {}

private:
  CUdeviceptr m_devicePtr;
};

#endif
