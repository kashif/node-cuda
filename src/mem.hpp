#ifndef MEM_HPP
#define MEM_HPP

#include <cuda.h>
#include "bindings.hpp"
#include "function.hpp"

namespace NodeCuda {

class Mem : public ObjectWrap {
public:
  static void Initialize(Handle<Object> target);

protected:
  static Persistent<FunctionTemplate> constructor_template;

  static Handle<Value> Alloc(const Arguments& args);
  static Handle<Value> AllocPitch(const Arguments& args);
  static Handle<Value> Free(const Arguments& args);
  static Handle<Value> CopyHtoD(const Arguments& args);
  static Handle<Value> CopyDtoH(const Arguments& args);

  static Handle<Value> GetDevicePtr(Local<String> property, const AccessorInfo &info);
  
  Mem() : ObjectWrap(), m_devicePtr(0) {}

  ~Mem() {}

private:
  static Handle<Value> New(const Arguments& args);

  CUdeviceptr m_devicePtr;

  friend class NodeCuda::Function;
};

}

#endif
