#include "cuda_device.hpp"

CudaDevice::CudaDevice(): EventEmitter() {
    cuDeviceGet(&m_device, 0);
}