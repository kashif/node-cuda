#ifndef MODULE_HPP
#define MODULE_HPP

#include <cuda.h>
#include "bindings.hpp"

class Module : public ObjectWrap {
public:
  static void Initialize(Handle<Object> target);

protected:
  static Persistent<FunctionTemplate> constructor_template;
  
  static Handle<Value> Load(const Arguments& args);
  
  Module() : ObjectWrap(), m_module(0) {}
  
  ~Module() {}

private:
  static Handle<Value> New(const Arguments& args);
  
  CUmodule m_module;
};

#endif
