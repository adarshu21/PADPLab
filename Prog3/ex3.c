#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <stdbool.h>

void print_arr(bool *X, long N){
	for(long i=2; i<N; i++)
		if(X[i]==1)			
			printf("%ld\t",i);
}

void Sieve_unfriendly(long N){
	/*
	Cache-unfriendly: load all data into memory directly
	Cache-friendly: load data in chunks into memory
	*/
	int ret_val = 0;//number of primes found
	bool *X = malloc(sizeof(bool)*N);
	for(long i=2; i<N; i++)
		X[i] = 1;
	
	double t = omp_get_wtime();
	for(long i=2; i<N; i++){
		
		if(X[i]==0)  //ignore if number has been sieved
			continue;
		//Sieve step
		for(long j=2*i; j<N; j+=i)
			X[j] = 0;
		}
	t = omp_get_wtime() - t;
	printf("Time taken for cache-unfriendly : %.8f\n",t);
	
	for(long i=2; i<N; i++)
		if(X[i]==1)
			ret_val++;
	//print_arr(X,N);
	free(X);
	printf("%d\n",ret_val);
	}

/*
Logic:
To find all primes between 1 to N, you have to explicitly find primes up to root(N).
Then, use these primes to filter out all composite numbers between root(N) to N.

There is no need to explicitly find primes between root(N) to N. 
Imagine number p>root(N). Then p*p>N, meaning p*p is beyond our range. 
Thus, there's no need for us to explicitly find p. The leftovers of the sieving operation will easily be primes.
*/

void Sieve_friendly(long N){
	
	int ret_val = 0;
	bool *X = malloc(sizeof(bool) * N);
	int root_N = (int)(sqrt(N));
	
	int factors[root_N];  //array of prime numbers upto root_N
	int factor_count = 0;
	
	//initialize array
	for(long i=2; i<N; i++)
		X[i] = 1;
	
	double t = omp_get_wtime();
	
	for(int i=2; i<=root_N; i++)
		{
		if(X[i]==0)
			continue;
	
		factors[factor_count] = i; //add i to the list of factors
		factor_count++;
		
		for(long j=2*i; j<=root_N; j+=i)
			X[j] = 0;
		}
	//All numbers from 1 to root(N) are handled
	//Handle from root(N)+1 to 2root(N), 2root(N)+1 to 3root(N) and so on...
	
	for(long i=root_N+1; i<N; i+=root_N)
		{
		long start;
		long end = (i+root_N-1) < N ? (i+root_N-1) : N; //basically min(i+root_N-1, N)
		for(int j = 0; j<factor_count; j++)
			{
			int temp_f = factors[j];
			
			start = i;
			if(start%temp_f != 0)//adjust starting value such that its a multiple of a prime
				start = i + (temp_f - i%temp_f); 
				
			for( ; start<=end; start+=temp_f )
				X[start] = 0;
			}
		for(long start = i; start<=end; start++)
			if(X[start]==1)
				ret_val++;
		}
	t = omp_get_wtime() - t;
	printf("Time taken for cache-friendly : %.8f\n",t);
	//print_arr(X,N);
	free(X);

	ret_val+=factor_count; //account for primes between 1 to root(N)
	printf("%d\n",ret_val);
	//return ret_val;
	}


void Sieve_parallel_friendly(long N){
	
	int ret_val = 0; //counts number of primes
	bool *X = malloc(sizeof(bool) * N);
	int root_N = (int)(sqrt(N));
	
	int factors[root_N];//array of prime numbers upto root_N
	int factor_count = 0;
	
	//initialize array
	for(long i=2; i<N; i++)
		X[i] = 1;
	
	double t = omp_get_wtime();
		
	for(int i=2; i<=root_N; i++)
		{
		if(X[i]==0)
			continue;
		//printf("%d\t",i);
		factors[factor_count] = i; //add i to the list of factors
		factor_count++;
		
		for(long j=2*i; j<=root_N; j+=i)
			X[j] = 0;
		}
	//All numbers from 1 to root(N) are handled
	//Handle from root(N)+1 to 2root(N), 2root(N)+1 to 3root(N) and so on...
	
	#pragma omp parallel for reduction(+:ret_val)
	for(long i=root_N+1; i<N; i+=root_N)
		{
		long start;
		long end = (i+root_N-1) < N ? (i+root_N-1) : N;  //basically min(i+root_N-1, N)
		for(int j = 0; j<factor_count; j++)
			{
			int temp_f = factors[j];
			
			start = i;
			if(start%temp_f != 0)//adjust starting value such that its a multiple of a prime
				start = i + (temp_f - i%temp_f); 
				
			for( ; start<=end; start+=temp_f )
				X[start] = 0;
			}
		for(long start = i; start<=end; start++)
			if(X[start]==1)
				ret_val++;
		}
	t = omp_get_wtime() - t;
	printf("Time taken for parallelized cache-friendly : %.8f\n",t);
	//print_arr(X,N);
	free(X);
	
	ret_val+=factor_count;//account for primes between 1 to root(N)
	printf("%d\n",ret_val);
	//return ret_val;
	}

int main(int argc, char *argv[]){
	long N = atoi(argv[1]) + 1;
	//int tnum = 4; //4 threads
		
	Sieve_unfriendly(N);	
	Sieve_friendly(N);
	Sieve_parallel_friendly(N);
	return 0;
}
