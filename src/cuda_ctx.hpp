#ifndef CUDA_CTX_HPP
#define CUDA_CTX_HPP

#include <cuda.h>
#include "bindings.hpp"

class CudaCtx : public EventEmitter
{
public:
  static void Initialize (Handle<Object> target);
  
protected:
  static Persistent<FunctionTemplate> constructor_template;
  static Handle<Value> New(const Arguments& args);
  static Handle<Value> destroy(const Arguments& args);
  
  CudaCtx () : EventEmitter () {
    m_context = NULL;
  }
  ~CudaCtx (){}

private:
  CUcontext m_context;
};
#endif