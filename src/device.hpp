#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <cuda.h>
#include "bindings.hpp"

namespace NodeCuda {

class Device : public ObjectWrap {
public:
  static void Initialize(Handle<Object> target);

protected:
  static Persistent<FunctionTemplate> constructor_template;

  static Handle<Value> New(const Arguments& args);
  static Handle<Value> GetComputeCapability(Local<String> property, const AccessorInfo &info);
  static Handle<Value> GetName(Local<String> property, const AccessorInfo &info);
  static Handle<Value> GetTotalMem(Local<String> property, const AccessorInfo &info);

  // TODO: cuDeviceGetAttribute
  // TODO: cuDeviceGetProperties

  Device() : ObjectWrap(), m_device(NULL) {}

  ~Device() {}

private:
  CUdevice m_device;

  friend class Ctx;
};

}

#endif
