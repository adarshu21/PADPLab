#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void init(int *X, int N){ //initializes matrix with random values
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			X[i*N + j] = rand()%100;
}

void display(int *X, int N, char c){  //code to display matrix, use it to prove correctness
	printf("Contents of matrix %c:\n",c);
	for(int i=0; i<N; i++)
		{
		for(int j=0; j<N; j++)
			printf("%d\t", X[i*N+j] );
		printf("\n");
		}
}

void process(int N, int tnum){  //initializes random arrays and performs matrix multiplication
	int *A = malloc(sizeof(int) * N*N );  //2d array
	int *B = malloc(sizeof(int) * N*N );  //2d array
	int *C = malloc(sizeof(int) * N*N );  //2d array
	init(A,N); //display(A,N, 'A');
	init(B,N); //display(B,N, 'B');
	
	double t = omp_get_wtime(); //start time
	#pragma omp parallel for num_threads(tnum)
	for(int i=0; i<N; i++)
		{
		for(int j=0; j<N; j++)
			{
			C[i*N+j] = 0;
			for(int k=0; k<N; k++)
				C[i*N+j] += A[i*N+k] * B[k*N+j];
			}
		}
	t = omp_get_wtime() - t; //time taken = end time - start time
	printf("%.4f\t",t); //output time taken, precision of 4 decimal places
	//display(C, N, 'C');
}


int main(int argc, char *argv[]){
	int N = atoi(argv[1]), tnum = atoi(argv[2]);
	/*
	printf("Enter size of matrix:");
	scanf("%d",&N);
	printf("Enter number of threads needed:");
	scanf("%d",&tnum);
	*/
	process(N,tnum);
}
