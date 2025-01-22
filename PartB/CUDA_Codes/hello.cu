#include <stdio.h>
#include <stdlib.h>


#define SIZE 1000

__global__ void helloKernel() {
    printf("Hello, CUDA!\n");
}


int main() {

	
  helloKernel<<<1, 10>>>();
    cudaDeviceSynchronize();
    return 0;
}
