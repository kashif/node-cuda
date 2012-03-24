#ifndef BINDINGS_HPP
#define BINDINGS_HPP

#include <v8.h>
#include <node.h>

using namespace v8;
using namespace node;

namespace NodeCuda {

static Handle<Value> GetDriverVersion(Local<String> property, const AccessorInfo &info);
static Handle<Value> GetDeviceCount(Local<String> property, const AccessorInfo &info);

}

#endif
