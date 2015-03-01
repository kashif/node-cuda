#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "bindings.hpp"

namespace NodeCuda {
  class Device : public ObjectWrap {
    public:
      static void Init(Handle<Object> exports);

    protected:
      static Persistent<FunctionTemplate> constructor_template;

      static NAN_METHOD(New);

      static NAN_GETTER(GetComputeCapability);
      static NAN_GETTER(GetName);
      static NAN_GETTER(GetTotalMem);

      // TODO: cuDeviceGetAttribute
      // TODO: cuDeviceGetProperties

      Device() : ObjectWrap(), m_device(0) {}
      ~Device() {}

    private:
      CUdevice m_device;
      //friend class Ctx;
  };
}

#endif
