#include <stdio.h>
#include <stdlib.h>


#define SIZE 1000
/*
__global__ void helloKernel() {
    printf("Hello, CUDA!\n");
}
*/

__global__ void count1s(int *arr, int *res)
	{
	__shared__ int x;
	int tid = threadIdx.x + blockIdx.x * blockDim.x;
	
	if(threadIdx.x==0)
		x = 0;
	__syncthreads();
	
	if(tid<SIZE && arr[tid]==1)
		atomicAdd(&x,1);
	__syncthreads();
	
	if (threadIdx.x == 0) {
        	atomicAdd(res, x);
    		}
	}

int main() {

	int myRes = 0;
	int A[SIZE];
	for(int i=0; i<SIZE; i++)
		myRes += (A[i] = rand()%2)==1?1:0;
	printf("Number of 1s from CPU: %d\n",myRes);	
  	myRes=0;  
  	
    int *res;
    int *arr;
    
    cudaMalloc(&arr, sizeof(A));
    
    cudaMalloc(&res, sizeof(int));
    cudaMemset(res, 0, sizeof(int));
    
    cudaMemcpy(arr, A, sizeof(A), cudaMemcpyHostToDevice);
    
    int blocks = (int)(SIZE/64)+1;
    count1s<<<blocks,64>>> (arr, res);
    
    cudaDeviceSynchronize();
    
    cudaMemcpy(&myRes, res, sizeof(int), cudaMemcpyDeviceToHost);
    
    printf("Number of 1s from GPU: %d\n",myRes);
    return 0;
}
