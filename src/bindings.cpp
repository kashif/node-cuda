#include "bindings.hpp"
#include "cuda_device.hpp"
#include "cuda_ctx.hpp"

extern "C"
void init (Handle<Object> target) {
  HandleScope scope;
  CudaDevice::Initialize(target);
  CudaCtx::Initialize(target);
}