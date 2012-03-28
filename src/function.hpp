#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <cuda.h>
#include "bindings.hpp"
#include "module.hpp"

namespace NodeCuda {

class Function : public ObjectWrap {
public:
  static void Initialize(Handle<Object> target);

protected:
  static Persistent<FunctionTemplate> constructor_template;

  static Handle<Value> LaunchKernel(const Arguments& args);

  Function() : ObjectWrap(), m_function(0) {}

  ~Function() {}

private:
  static Handle<Value> New(const Arguments& args);

  CUfunction m_function;

  friend Handle<Value> Module::GetFunction(const Arguments&);
};

}

#endif
