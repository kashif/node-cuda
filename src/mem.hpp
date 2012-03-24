#ifndef MEM_HPP
#define MEM_HPP

#include <cuda.h>
#include "bindings.hpp"

class Mem : public ObjectWrap {
public:
  static void Initialize(Handle<Object> target);

protected:
  static Persistent<FunctionTemplate> constructor_template;
  
  static Handle<Value> Alloc(const Arguments& args);
  static Handle<Value> AllocPitch(const Arguments& args);
  static Handle<Value> Free(const Arguments& args);

  Mem() : ObjectWrap(), m_devicePtr(0) {}
  
  ~Mem() {}

private:
  static Handle<Value> New(const Arguments& args);
  
  CUdeviceptr m_devicePtr;
};

#endif
