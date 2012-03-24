#include <cstdio>

__global__ void helloWorld() {
#if __CUDA_ARCH__ >= 200
  printf("Hello, world!");
#endif
}
