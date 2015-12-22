#include "device.hpp"

using namespace NodeCuda;

Nan::Persistent<v8::Function> Device::constructor;

NAN_MODULE_INIT(Device::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(Device::New);
  tpl->SetClassName(Nan::New("Device").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "name", Device::GetName);
  Nan::SetPrototypeMethod(tpl, "totalMem", Device::GetTotalMem);
  Nan::SetPrototypeMethod(tpl, "computeCapability", Device::GetComputeCapability);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("Device").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(Device::New) {
  if (info.IsConstructCall()) {
    int ordinal = info[0]->IsUndefined() ? 0 : Nan::To<int>(info[0]).FromJust();
    Device *pdevice = new Device();
    cuDeviceGet(&(pdevice->m_device), ordinal);
    pdevice->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = {info[0]};
    v8::Local<v8::Function> cons = Nan::New(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

NAN_METHOD(Device::GetComputeCapability) {
  int major = 0, minor = 0;

  Device *pdevice = Nan::ObjectWrap::Unwrap<Device>(info.This());
  cuDeviceComputeCapability(&major, &minor, pdevice->m_device);

  v8::Local<v8::Object> result = Nan::New<v8::Object>();

  Nan::Set(result, Nan::New("major").ToLocalChecked(), Nan::New(major));
  Nan::Set(result, Nan::New("minor").ToLocalChecked(), Nan::New(minor));
  info.GetReturnValue().Set(result);
}

NAN_METHOD(Device::GetName) {
  char deviceName[256];

  Device *pdevice = Nan::ObjectWrap::Unwrap<Device>(info.This());
  cuDeviceGetName(deviceName, 256, pdevice->m_device);

  info.GetReturnValue().Set(Nan::New(deviceName).ToLocalChecked());
}

NAN_METHOD(Device::GetTotalMem) {
  size_t totalGlobalMem;

  Device *pdevice = Nan::ObjectWrap::Unwrap<Device>(info.This());
  cuDeviceTotalMem(&totalGlobalMem, pdevice->m_device);

  v8::Local<v8::Number> result = Nan::New((double)totalGlobalMem);
  info.GetReturnValue().Set(result);
}
