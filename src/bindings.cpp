#include "bindings.hpp"
#include "cuda_device.hpp"

extern "C"
void init (Handle<Object> target) {
  HandleScope scope;
  CudaDevice::Initialize(target);
}