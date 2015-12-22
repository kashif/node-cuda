#ifndef BINDINGS_HPP
#define BINDINGS_HPP

#include <nan.h>
#include <cuda.h>

namespace NodeCuda {
  NAN_METHOD(GetDriverVersion);
  NAN_METHOD(GetDeviceCount);
}

#endif
