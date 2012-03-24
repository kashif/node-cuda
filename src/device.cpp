#include "device.hpp"

Persistent<FunctionTemplate> Device::constructor_template;

void Device::Initialize(Handle<Object> target) {
  HandleScope scope;

  Local<FunctionTemplate> t = FunctionTemplate::New(Device::New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("Device"));

  constructor_template->InstanceTemplate()->SetAccessor(String::New("name"), Device::Name);
  constructor_template->InstanceTemplate()->SetAccessor(String::New("totalMem"), Device::TotalMem);
  constructor_template->InstanceTemplate()->SetAccessor(String::New("computeCapability"), Device::ComputeCapability);

  target->Set(String::NewSymbol("Device"), constructor_template->GetFunction());
}

static Handle<Value> GetName(CUdevice device) {
  HandleScope scope;
  char deviceName[256];
  
  cuDeviceGetName(deviceName, 256, device);
  Local<String> result = String::New(deviceName);
  return scope.Close(result);
}

Handle<Value> Device::New(const Arguments& args) {
  HandleScope scope;
  int ordinal = args[0]->IntegerValue();

  if (constructor_template->HasInstance(args.This())) {
    Device *cu = new Device();
    cuDeviceGet(&(cu->m_device), ordinal);

    cu->Wrap(args.This());
    return args.This();
  
  } else {
    CUdevice device;
    
    cuDeviceGet(&device, ordinal);
    return GetName(device);
  }
}

Handle<Value> Device::ComputeCapability(Local<String> property, const AccessorInfo &info) {
  HandleScope scope;

  Device *cu = ObjectWrap::Unwrap<Device>(info.Holder());
  int major = 0, minor = 0;
  cuDeviceComputeCapability(&major, &minor, cu->m_device);
  
  Local<Object> result = Object::New();
  result->Set(String::New("major"), Integer::New(major));
  result->Set(String::New("minor"), Integer::New(minor));
  return scope.Close(result);
}

Handle<Value> Device::Name(Local<String> property, const AccessorInfo &info) {
  HandleScope scope;

  Device *cu = ObjectWrap::Unwrap<Device>(info.Holder());
  return GetName(cu->m_device);
}

Handle<Value> Device::TotalMem(Local<String> property, const AccessorInfo &info) {
  HandleScope scope;

  Device *cu = ObjectWrap::Unwrap<Device>(info.Holder());
  size_t totalGlobalMem;
  cuDeviceTotalMem(&totalGlobalMem, cu->m_device);
  
  return scope.Close(Number::New(totalGlobalMem));
}
