#ifndef CUDA_CTX_HPP
#define CUDA_CTX_HPP

#include <cuda.h>
#include "bindings.hpp"

class CudaCtx : public ObjectWrap {
public:
  static void Initialize(Handle<Object> target);
  
protected:
  static Persistent<FunctionTemplate> constructor_template;
  
  static Handle<Value> New(const Arguments& args);
  static Handle<Value> destroy(const Arguments& args);
  static Handle<Value> pushCurrent(const Arguments& args);
  static Handle<Value> popCurrent(const Arguments& args);
  static Handle<Value> setCurrent(const Arguments& args);
  static Handle<Value> getCurrent(const Arguments& args);
  static Handle<Value> synchronize(const Arguments& args);
  static Handle<Value> getApiVersion(const Arguments& args);

  CudaCtx() : ObjectWrap(), m_context(NULL) {}
  
  ~CudaCtx () {}

private:
  CUcontext m_context;
};
#endif
