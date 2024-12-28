#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int process(int iter_num)
	{  	
	float x=0, y=0; //random x and y coordinates initialized in loop
	int N = 0; //number of points that lay within circle
	
	for(int i=0; i < iter_num; i++)
		{
		x = (float)rand()/RAND_MAX;
		y = (float)rand()/RAND_MAX;
		if(x*x + y*y <= 1)
			N++;
		}
	return N;
	}

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Invalid number of arguments. exiting...\n");
		return 1;
		}
	float t;
	int rank, num_processes;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&num_processes);
	
	int N = atoi(argv[1]);    //number of iterations per processor
	srand(time(NULL)+rank); 
	t = MPI_Wtime();
	int res = process(N);
	t = MPI_Wtime() - t; 
	printf("Time taken to compute for process %d: %.4f\n",rank,t);
	if(rank==0)
		{
		int temp = 0;
		t = MPI_Wtime();
		for(int i=1; i<num_processes; i++)
			{
			//receive value here	
					
			MPI_Recv(&temp, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			//printf("%d\n",temp);
			res+=temp;
			}
		t = MPI_Wtime() - t;
		printf("Time taken to gather messages: %.4f\n",t);
		//printf("Total = %d\n",res);
		float PI = (float)(4*res) / (num_processes*N);
		printf("PI=%.4f\n",PI);
		}
	else
		{
		MPI_Send(&res, 1, MPI_INT, 0,0,MPI_COMM_WORLD);
		}
	
	MPI_Finalize();
	return 0;
}
