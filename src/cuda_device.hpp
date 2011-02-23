#ifndef CUDA_DEVICE_HPP
#define CUDA_DEVICE_HPP

#include <cuda.h>

#include "bindings.hpp"

class CudaDevice : public EventEmitter {
public:
    static void Initialize (Handle<Object> target);
    static Persistent<FunctionTemplate> constructor_template;

protected:
    CUdevice m_device;

    CudaDevice();
    ~CudaDevice();
};

#endif