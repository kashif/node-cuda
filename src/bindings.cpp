#include "bindings.hpp"
// #include "ctx.hpp"
#include "device.hpp"
// #include "function.hpp"
// #include "mem.hpp"
// #include "module.hpp"

using namespace NodeCuda;

void InitAll (Handle<Object> exports) {
  // Initiailze the cuda driver api
  cuInit(0);

  // These methods don't need instances
  exports->SetAccessor(NanNew<String>("driverVersion"),
    GetDriverVersion);
  exports->SetAccessor(NanNew<String>("deviceCount"),
    GetDeviceCount);

  // Initialize driver api bindings
  // Ctx::Initialize(exports);
  Device::Init(exports);
  // NodeCuda::Function::Initialize(exports);
  // Mem::Initialize(exports);
  // Module::Initialize(exports);
}

NAN_GETTER(NodeCuda::GetDriverVersion) {
  NanScope();

  int driverVersion = 0;
  cuDriverGetVersion(&driverVersion);
  NanReturnValue(NanNew<Integer>(driverVersion));
}

NAN_GETTER(NodeCuda::GetDeviceCount) {
  NanScope();

  int count = 0;
  cuDeviceGetCount(&count);
  NanReturnValue(NanNew<Integer>(count));
}

NODE_MODULE(cuda, InitAll);
