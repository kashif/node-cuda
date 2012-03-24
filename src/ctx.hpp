#ifndef CTX_HPP
#define CTX_HPP

#include <cuda.h>
#include "bindings.hpp"

namespace NodeCuda {

class Ctx : public ObjectWrap {
public:
  static void Initialize(Handle<Object> target);
  
protected:
  static Persistent<FunctionTemplate> constructor_template;
  
  static Handle<Value> New(const Arguments& args);
  static Handle<Value> Destroy(const Arguments& args);
  static Handle<Value> PushCurrent(const Arguments& args);
  static Handle<Value> PopCurrent(const Arguments& args);
  static Handle<Value> SetCurrent(const Arguments& args);
  static Handle<Value> GetCurrent(const Arguments& args);
  static Handle<Value> Synchronize(const Arguments& args);
  static Handle<Value> GetApiVersion(Local<String> property, const AccessorInfo &info);

  Ctx() : ObjectWrap(), m_context(NULL) {}
  
  ~Ctx () {}

private:
  CUcontext m_context;
};

}

#endif
