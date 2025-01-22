/*
Counts number of 1s in an array
*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000

__global__ void count1s(int *arr, int *res)
	{
	__shared__ int val; //creates shared memory for all threads in thread block
	int tid = threadIdx.x + blockIdx.x * blockDim.x; //find index according to array
	
	if(threadIdx.x==0)
		val = 0; //per block, assign one thread to value 0
	__syncthreads();
	
	if(tid<SIZE && arr[tid]==1) //per block, keep sum of number of 1s
		atomicAdd(&val,1); 
	__syncthreads();
	
	if (threadIdx.x == 0) { //master thread per block updates result variable
        	atomicAdd(res, val);
    		}
	}

int main() {

	int myRes = 0;
	int A[SIZE];
	for(int i=0; i<SIZE; i++)
		myRes += (A[i] = rand()%2)==1?1:0;
	printf("Number of 1s from CPU: %d\n",myRes);	
  	myRes=0;  
  	
    int *res; //stores result
    int *arr; //stores array A
        
    cudaMalloc(&res, sizeof(int));
    cudaMemset(res, 0, sizeof(int));
    
    cudaMalloc(&arr, sizeof(A));
    cudaMemcpy(arr, A, sizeof(A), cudaMemcpyHostToDevice);
    
    int blocks = (int)(SIZE/64)+1;
    count1s<<<blocks,64>>> (arr, res);
    
//    cudaDeviceSynchronize();
    
    cudaMemcpy(&myRes, res, sizeof(int), cudaMemcpyDeviceToHost);
    
    printf("Number of 1s from GPU: %d\n",myRes);
    return 0;
}
