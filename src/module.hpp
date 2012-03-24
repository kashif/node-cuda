#ifndef MODULE_HPP
#define MODULE_HPP

#include <cuda.h>
#include "bindings.hpp"

namespace NodeCuda {

class Module : public ObjectWrap {
public:
  static void Initialize(Handle<Object> target);
  static Handle<Value> GetFunction(const Arguments& args);

protected:
  static Persistent<FunctionTemplate> constructor_template;
  
  static Handle<Value> Load(const Arguments& args);
  
  Module() : ObjectWrap(), m_module(0) {}
  
  ~Module() {}

private:
  static Handle<Value> New(const Arguments& args);
  
  CUmodule m_module;
};

}

#endif
