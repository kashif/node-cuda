#include "ctx.hpp"
#include "device.hpp"

using namespace NodeCuda;

Persistent<FunctionTemplate> Ctx::constructor_template;

void Ctx::Initialize(Handle<Object> target) {
  HandleScope scope;

  Local<FunctionTemplate> t = FunctionTemplate::New(Ctx::New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(String::NewSymbol("CudaCtx"));

  NODE_SET_PROTOTYPE_METHOD(constructor_template, "destroy", Ctx::Destroy);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "pushCurrent", Ctx::PushCurrent);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "popCurrent", Ctx::PopCurrent);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "setCurrent", Ctx::SetCurrent);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "getCurrent", Ctx::GetCurrent);
  NODE_SET_PROTOTYPE_METHOD(constructor_template, "synchronize", Ctx::Synchronize);
  constructor_template->InstanceTemplate()->SetAccessor(String::New("apiVersion"), Ctx::GetApiVersion);

  target->Set(String::NewSymbol("Ctx"), constructor_template->GetFunction());
}

Handle<Value> Ctx::New(const Arguments& args) {
  HandleScope scope;

  Ctx *pctx = new Ctx();
  pctx->Wrap(args.This());

  unsigned int flags = args[0]->Uint32Value();
  pctx->m_device = ObjectWrap::Unwrap<Device>(args[1]->ToObject())->m_device;

  cuCtxCreate(&(pctx->m_context), flags, pctx->m_device);

  return args.This();
}

Handle<Value> Ctx::Destroy(const Arguments& args) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(args.This());

  CUresult error = cuCtxDestroy(pctx->m_context);
  return scope.Close(Number::New(error));
}

Handle<Value> Ctx::PushCurrent(const Arguments& args) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(args.This());

  CUresult error = cuCtxPushCurrent(pctx->m_context);
  return scope.Close(Number::New(error));
}

Handle<Value> Ctx::PopCurrent(const Arguments& args) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(args.This());

  CUresult error = cuCtxPopCurrent(&(pctx->m_context));
  return scope.Close(Number::New(error));
}

Handle<Value> Ctx::SetCurrent(const Arguments& args) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(args.This());

  CUresult error = cuCtxSetCurrent(pctx->m_context);
  return scope.Close(Number::New(error));
}

Handle<Value> Ctx::GetCurrent(const Arguments& args) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(args.This());

  CUresult error = cuCtxGetCurrent(&(pctx->m_context));
  return scope.Close(Number::New(error));
}

struct SynchronizeParams {
  Ctx *ctx;
  CUresult error;
  Persistent<Function> cb;
};

Handle<Value> Ctx::Synchronize(const Arguments& args) {
  HandleScope scope;

  if (args.Length() >= 1 && args[0]->IsFunction()) {
    // Asynchronous
    Local<Function> cb = Local<Function>::Cast(args[0]);

    Ctx *ctx = ObjectWrap::Unwrap<Ctx>(args.This());
    if (ctx->sync_in_progress)
      return scope.Close(Number::New(-1));

    SynchronizeParams *params = new SynchronizeParams();
    params->ctx = ctx;
    params->cb = Persistent<Function>::New(cb);

    cuCtxPopCurrent(NULL);

    // build up the work request
    uv_work_t* work_req = new uv_work_t;
    work_req->data = params;

    uv_queue_work(uv_default_loop(),
        work_req,
        Process,
        After);
    uv_ref((uv_handle_t*) &work_req);

    ctx->Ref();
    ctx->sync_in_progress = true;

    return Undefined();

  } else {
    // Synchronous
    CUresult error = cuCtxSynchronize();
    return scope.Close(Number::New(error));
  }
}

void Ctx::Process(uv_work_t* work_req) {
  SynchronizeParams *params = static_cast<SynchronizeParams*>(work_req->data);

  params->error = cuCtxPushCurrent(params->ctx->m_context);
  if (params->error) return;

  params->error = cuCtxSynchronize();
  if (params->error) return;

  params->error = cuCtxPopCurrent(NULL);
}

void Ctx::After(uv_work_t* work_req, int status) {
  assert(status == 0);
  HandleScope scope;
  SynchronizeParams *params = static_cast<SynchronizeParams*>(work_req->data);

  params->ctx->Unref();
  params->ctx->sync_in_progress = false;

  cuCtxPushCurrent(params->ctx->m_context);

  Local<Value> argv[1];
  argv[0] = Number::New(params->error);

  TryCatch try_catch;
  params->cb->Call(Context::GetCurrent()->Global(), 1, argv);
  if (try_catch.HasCaught()) FatalException(try_catch);

  params->cb.Dispose();
  uv_unref((uv_handle_t*) work_req);
  delete params;
}

Handle<Value> Ctx::GetApiVersion(Local<String> property, const AccessorInfo &info) {
  HandleScope scope;
  Ctx *pctx = ObjectWrap::Unwrap<Ctx>(info.Holder());

  unsigned int version;
  CUresult error = cuCtxGetApiVersion(pctx->m_context, &version);

  return scope.Close(Number::New(version));
}
