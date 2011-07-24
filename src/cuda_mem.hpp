#ifndef CUDA_MEM_HPP
#define CUDA_MEM_HPP

#include <cuda.h>
#include "bindings.hpp"

class CudaMem : public EventEmitter {
public:
  static Persistent<FunctionTemplate> constructor_template;
  static void Initialize (Handle<Object> target);
  static Handle<Value> New(const Arguments& args);
  static Handle<Value> alloc(const Arguments& args);
  static Handle<Value> allocPitch(const Arguments& args);
  static Handle<Value> free(const Arguments& args);

  CUdeviceptr m_devicePtr;
protected:
  CudaMem () : EventEmitter () {
    m_devicePtr = 0;
  }
  ~CudaMem (){}
};

#endif