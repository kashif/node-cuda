#include <cstdio>

extern "C" {
  __global__ void helloWorld(char *data) {
    #if __CUDA_ARCH__ >= 200
    printf("Hello, world! I'm thread (%d,%d,%d) in block (%d,%d,%d).\n",
      threadIdx.x, threadIdx.y, threadIdx.z,
      blockIdx.x, blockIdx.y, blockIdx.z);
    #endif

    int sum = 0;
    for (int i=0; i<100; i++) {
      sum += data[i];
    }
    
    #if __CUDA_ARCH__ >= 200
    printf("The sum is: %d\n", sum);
    #endif
  }
}
