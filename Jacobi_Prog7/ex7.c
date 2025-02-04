#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>
#include <float.h>

double get_max(double x, double y){
	if(x>y)
		return x;
	return y;
}

void print_arr(double *A, int N){	
	for(int i=0; i<N; i++)
		{
		for(int j=0; j<N; j++)
			printf("%.2f\t",A[N*i+j]);
		printf("\n");
		}
}


//arg list - matrix size, max_iterations and max tolerance
int main(int argc, char *argv[]){

	struct timespec start, end;
	double elapsed_time;
	
	int max_iter, n, n2;
	double tol, max_diff=DBL_MAX;	
//	printf("Enter matrix size, max_iterations and max tolerance: ");
	//scanf("%d%d%lf", &n, &max_iter, &tol);
	n = atoi(argv[1]);
	max_iter = atoi(argv[2]);
	tol = atof(argv[3]);
	printf("%d\t%d\t%lf\n",n,max_iter,tol);
	n2 = n+2; //add a bit of padding to matrix
	
	double *T,  *T_new; 
	double *temp = NULL;
	T = (double *)malloc(sizeof(double)*n2*n2);
	T_new = (double *)malloc(sizeof(double)*n2*n2);
	
	if(T==NULL||T_new==NULL)
	{
		printf("\nNot enough space");
		exit(0);
	}
	
	for(int i=1;i<=n;i++)
	{
		T[ n*n2 + i ] =  (i*100)/(n+1);
		T[ n2*i + n ] =(i*100)/(n+1); 
	}	
	print_arr(T,n2); printf("\n");
//	print_arr(T_new,n2); printf("\n");
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(int x=1; x<=max_iter && max_diff>tol; x++) //iterate max_iter times or until max_diff<=tolerance
		{
		max_diff = 0; //reinitialize max difference to 0
		for(int i=1; i<=n; i++)
			{
			for(int j=1; j<=n; j++)
				{
				T_new[n2*i+j] = 0.25*(T[n2*i+j-1] + T[n2*i+j+1] + T[(i-1)*n2+j] + T[(i+1)*n2+j]);
				//T_new = sum of neighbouring 4 values/4
				max_diff = get_max(max_diff, fabs( T_new[n2*i+j] - T[n2*i+j] ));				
				}
			}
		temp = T;
		T = T_new;
		T_new = temp;
		print_arr(T,n2); printf("\n");
		}
	clock_gettime(CLOCK_MONOTONIC, &end);
	elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1e9;
	//t = omp_get_wtime() - t;
	printf("Time taken = %.4fs\n",elapsed_time);
	
	//print_arr(T,n2);
}

