#ifndef MEM_HPP
#define MEM_HPP

#include <cuda.h>
#include "bindings.hpp"

class Mem : public ObjectWrap {
public:
  static void Initialize(Handle<Object> target);

protected:
  static Persistent<FunctionTemplate> constructor_template;
  
  static Handle<Value> New(const Arguments& args);
  static Handle<Value> alloc(const Arguments& args);
  static Handle<Value> allocPitch(const Arguments& args);
  static Handle<Value> free(const Arguments& args);

  Mem() : ObjectWrap(), m_devicePtr(0) {}
  
  ~Mem() {}

private:
  CUdeviceptr m_devicePtr;
};

#endif
