#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <cuda.h>
#include "bindings.hpp"

class Device : public ObjectWrap {
public:
  static void Initialize(Handle<Object> target);

protected:
  static Persistent<FunctionTemplate> constructor_template;

  static Handle<Value> New(const Arguments& args);
  static Handle<Value> ComputeCapability(Local<String> property, const AccessorInfo &info);
  static Handle<Value> Name(Local<String> property, const AccessorInfo &info);
  static Handle<Value> TotalMem(Local<String> property, const AccessorInfo &info);

  Device() : ObjectWrap(), m_device(NULL) {}

  ~Device() {}

private:
  CUdevice m_device;

  friend class Ctx;
};

#endif
