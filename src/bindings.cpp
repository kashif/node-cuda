#include "bindings.hpp"
//#include "ctx.hpp"
#include "device.hpp"
// #include "function.hpp"
// #include "mem.hpp"
// #include "module.hpp"

using namespace NodeCuda;
using v8::FunctionTemplate;

NAN_MODULE_INIT(InitAll) {
  // Initiailze the cuda driver api
  cuInit(0);

  // These methods don't need instances
  Nan::Set(target, Nan::New("getDriverVersion").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(GetDriverVersion)).ToLocalChecked());
  Nan::Set(target, Nan::New("getDeviceCount").ToLocalChecked(),
      Nan::GetFunction(Nan::New<FunctionTemplate>(GetDeviceCount)).ToLocalChecked());

  // Initialize driver api bindings
  // Ctx::Initialize(target);
  Device::Init(target);
  // NodeCuda::Function::Initialize(target);
  // Mem::Initialize(target);
  // Module::Initialize(target);
}

NAN_METHOD(NodeCuda::GetDriverVersion) {
  int driverVersion = 0;
  cuDriverGetVersion(&driverVersion);

  info.GetReturnValue().Set(Nan::New(driverVersion));
}

NAN_METHOD(NodeCuda::GetDeviceCount) {
  int count = 0;
  cuDeviceGetCount(&count);

  info.GetReturnValue().Set(Nan::New(count));
}

NODE_MODULE(cuda, InitAll);
