#include "bindings.hpp"
#include "cuda_device.hpp"
#include "cuda_ctx.hpp"
#include "cuda_mem.hpp"

extern "C"
void init (Handle<Object> target) {
  HandleScope scope;
  CudaDevice::Initialize(target);
  CudaCtx::Initialize(target);
  CudaMem::Initialize(target);
}