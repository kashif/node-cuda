#include "device.hpp"

using namespace NodeCuda;

Persistent<FunctionTemplate> Device::constructor_template;

void Device::Init(Handle<Object> target) {
  NanScope();

  Local<FunctionTemplate> t = NanNew<FunctionTemplate>(New);
  t->InstanceTemplate()->SetInternalFieldCount(1);
  t->SetClassName(NanNew("CudaDevice"));

  t->InstanceTemplate()->SetAccessor(NanNew<String>("name"),
    GetName);
  t->InstanceTemplate()->SetAccessor(NanNew<String>("totalMem"),
    GetTotalMem);
  t->InstanceTemplate()->SetAccessor(NanNew<String>("computeCapability"),
    GetComputeCapability);

  NanAssignPersistent(constructor_template, t);

  target->Set(NanNew<String>("Device"), t->GetFunction());
}

NAN_METHOD(Device::New) {
  NanScope();
  int ordinal = args[0]->IsUndefined() ? 0 : args[0]->IntegerValue();

  Device *pdevice = new Device();
  cuDeviceGet(&(pdevice->m_device), ordinal);

  pdevice->Wrap(args.This());
  NanReturnValue(args.This());
}

NAN_GETTER(Device::GetComputeCapability) {
  NanScope();

  Device *pdevice = ObjectWrap::Unwrap<Device>(args.This());

  int major = 0, minor = 0;
  cuDeviceComputeCapability(&major, &minor, pdevice->m_device);

  Local<Object> result = NanNew<Object>();
  result->Set(NanNew<String>("major"), NanNew<Integer>(major));
  result->Set(NanNew<String>("minor"), NanNew<Integer>(minor));
  NanReturnValue(result);
}

NAN_GETTER(Device::GetName) {
  NanScope();
  char deviceName[1024];

  Device *pdevice = ObjectWrap::Unwrap<Device>(args.This());
  cuDeviceGetName(deviceName, sizeof(deviceName), pdevice->m_device);

  NanReturnValue(NanNew<String>(deviceName));
}

NAN_GETTER(Device::GetTotalMem) {
  NanScope();
  size_t totalGlobalMem;

  Device *pdevice = ObjectWrap::Unwrap<Device>(args.This());
  cuDeviceTotalMem(&totalGlobalMem, pdevice->m_device);

  NanReturnValue(NanNew<Number>(totalGlobalMem));
}
