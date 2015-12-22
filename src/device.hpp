#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "bindings.hpp"

namespace NodeCuda {

  class Device : public Nan::ObjectWrap {
    public:
      static NAN_MODULE_INIT(Init);

    protected:
      static Nan::Persistent<v8::Function> constructor;

      static NAN_METHOD(New);
      static NAN_METHOD(GetComputeCapability);
      static NAN_METHOD(GetName);
      static NAN_METHOD(GetTotalMem);

      // TODO: cuDeviceGetAttribute
      // TODO: cuDeviceGetProperties

      Device() : m_device(NULL) {}
      ~Device() {}

    private:
      CUdevice m_device;

      //friend class Ctx;
  };

}

#endif
