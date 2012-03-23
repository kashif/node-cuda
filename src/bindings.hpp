#ifndef BINDINGS_HPP
#define BINDINGS_HPP

#include <v8.h>
#include <node.h>

using namespace v8;
using namespace node;

static Handle<Value> driverGetVersion(const Arguments& args);
static Handle<Value> deviceGetCount(const Arguments& args);

#endif
