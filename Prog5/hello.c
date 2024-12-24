#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
	{
	int rank, res_len;
	char name[MPI_MAX_PROCESSOR_NAME]; 
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(&name, &res_len);
	printf("Hello from rank %d and processor %s\n",rank, name);

	MPI_Finalize(); //terminate the MPI execution environment
	
	return 0;
	}
