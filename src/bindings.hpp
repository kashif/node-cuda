#ifndef BINDINGS_HPP
#define BINDINGS_HPP

#include <node.h>
#include <node_object_wrap.h>
#include <nan.h>
#include <cuda.h>

using namespace v8;
using namespace node;

namespace NodeCuda {
  static NAN_GETTER(GetDriverVersion);
  static NAN_GETTER(GetDeviceCount);
}

#endif
