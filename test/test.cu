#include <cstdio>

extern "C" {
  __global__ void helloWorld() {
    #if __CUDA_ARCH__ >= 200
    printf("Hello, world! I'm thread (%d,%d,%d) in block (%d,%d,%d).\n",
      threadIdx.x, threadIdx.y, threadIdx.z,
      blockIdx.x, blockIdx.y, blockIdx.z);
    #endif
  }
}
