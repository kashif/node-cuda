#ifndef CTX_HPP
#define CTX_HPP

#include <cuda.h>
#include "bindings.hpp"
#include "device.hpp"

namespace NodeCuda {

class Ctx : public ObjectWrap {
public:
  static void Initialize(Handle<Object> target);
  
protected:
  static Persistent<FunctionTemplate> constructor_template;
  
  static Handle<Value> New(const Arguments& args);
  static Handle<Value> Destroy(const Arguments& args);
  static Handle<Value> PushCurrent(const Arguments& args);
  static Handle<Value> PopCurrent(const Arguments& args);
  static Handle<Value> SetCurrent(const Arguments& args);
  static Handle<Value> GetCurrent(const Arguments& args);
  static Handle<Value> Synchronize(const Arguments& args);
  static Handle<Value> GetApiVersion(Local<String> property, const AccessorInfo &info);

  Ctx() : ObjectWrap(), m_context(NULL), m_device(0), sync_in_progress(false) {}
  
  ~Ctx () {}

private:
  CUcontext m_context;
  CUdevice m_device;
  
  bool sync_in_progress;

  static void EIO_Synchronize(eio_req *req);
  static int EIO_AfterSynchronize(eio_req *req);
};

}

#endif
