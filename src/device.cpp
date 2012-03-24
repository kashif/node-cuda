#include "device.hpp"

using namespace NodeCuda;

Persistent<FunctionTemplate> Device::constructor_template;

void Device::Initialize(Handle<Object> target) {
  HandleScope scope;

  Local<FunctionTemplate> t = FunctionTemplate::New(Device::New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("CudaDevice"));

  constructor_template->InstanceTemplate()->SetAccessor(String::New("name"), Device::GetName);
  constructor_template->InstanceTemplate()->SetAccessor(String::New("totalMem"), Device::GetTotalMem);
  constructor_template->InstanceTemplate()->SetAccessor(String::New("computeCapability"), Device::GetComputeCapability);

  target->Set(String::NewSymbol("Device"), constructor_template->GetFunction());
}

static Handle<Value> GetName_(CUdevice device) {
  HandleScope scope;
  char deviceName[256];
  
  cuDeviceGetName(deviceName, 256, device);
  Local<String> result = String::New(deviceName);
  return scope.Close(result);
}

Handle<Value> Device::New(const Arguments& args) {
  HandleScope scope;
  Local<Object> result = args.This();
  int ordinal = args[0]->IntegerValue();

  if (!constructor_template->HasInstance(result)) {
    result = constructor_template->InstanceTemplate()->NewInstance();
  }
  
  Device *pdevice = new Device();
  cuDeviceGet(&(pdevice->m_device), ordinal);

  pdevice->Wrap(result);
  return scope.Close(result);
}

Handle<Value> Device::GetComputeCapability(Local<String> property, const AccessorInfo &info) {
  HandleScope scope;

  Device *pdevice = ObjectWrap::Unwrap<Device>(info.Holder());
  int major = 0, minor = 0;
  cuDeviceComputeCapability(&major, &minor, pdevice->m_device);
  
  Local<Object> result = Object::New();
  result->Set(String::New("major"), Integer::New(major));
  result->Set(String::New("minor"), Integer::New(minor));
  return scope.Close(result);
}

Handle<Value> Device::GetName(Local<String> property, const AccessorInfo &info) {
  HandleScope scope;

  Device *pdevice = ObjectWrap::Unwrap<Device>(info.Holder());
  return GetName_(pdevice->m_device);
}

Handle<Value> Device::GetTotalMem(Local<String> property, const AccessorInfo &info) {
  HandleScope scope;

  Device *pdevice = ObjectWrap::Unwrap<Device>(info.Holder());
  size_t totalGlobalMem;
  cuDeviceTotalMem(&totalGlobalMem, pdevice->m_device);
  
  return scope.Close(Number::New(totalGlobalMem));
}
