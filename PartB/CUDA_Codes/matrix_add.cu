#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

__global__ void matrixAdd(int *A, int *B, int *C){
	
	int row = threadIdx.x + blockIdx.x * blockDim.x;
	int col = threadIdx.y + blockIdx.y * blockDim.y;
	
	//global index = row * max_num_of_cols + col
	int idx = row*SIZE + col; //column max size is hardcoded here
	
	C[idx] = A[idx] + B[idx];		
	
	}

void arr_init(int arr[SIZE][SIZE]){
	
	for(int i=0; i<SIZE; i++)
		for(int j=0; j<SIZE; j++)
			arr[i][j] = rand()%10;
}

void print_arr(int arr[SIZE][SIZE], char ch){
	printf("Array %c:\n",ch);
	for(int i=0; i<SIZE; i++)
		{
		for(int j=0; j<SIZE; j++)
			printf("%d\t",arr[i][j]);
		printf("\n");
		}
}
int main(){
	int A[SIZE][SIZE];
	int B[SIZE][SIZE];
	int C[SIZE][SIZE];
	arr_init(A); print_arr(A, 'A');
	arr_init(B); print_arr(B, 'B');
	
	int *arr_a, *arr_b, *arr_c;
	cudaMalloc(&arr_a, sizeof(A));
	cudaMalloc(&arr_b, sizeof(B));
	cudaMalloc(&arr_c, sizeof(C));
	
	cudaMemcpy(arr_a, A, sizeof(A), cudaMemcpyHostToDevice);
	cudaMemcpy(arr_b, B, sizeof(B), cudaMemcpyHostToDevice);
	
	dim3 blockDim(16,16); //create thread block of 16*16 threads
	
	matrixAdd<<<1,blockDim>>> (arr_a, arr_b, arr_c);
	cudaMemcpy(C, arr_c, sizeof(C), cudaMemcpyDeviceToHost);
	
	print_arr(C,'C');
	cudaFree(arr_a);
    	cudaFree(arr_b);
   	cudaFree(arr_c);
	
	return 0;
}
