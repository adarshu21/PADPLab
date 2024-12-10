#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void process(int iter_num, int tnum)
	{  	
	/*
	Monte Carlo theory: 
	Assume you have square of side length 'a'. A circle is inscribed within square, meaning it has radius 'a/2'.
	Ratio of areas between square and circle is 4/Pi.
	Therefore, Pi =  4 * area of circle / area of square
	
	Method:
	Randomly disperse 'X' number of points within the square.
	Find out how many of these 'X' points lie within circle. Call this number 'N'
	Pi = 4*N / X
	
	Implementation:
	Total number of points here = iter_num i.e. number of iterations
	Number of points within circle is measured by N.
	Thus, PI = 4*N / (iter_num)
	*/
	int x=0, y=0; //random x and y coordinates initialized in loop
	int N = 0; //number of points that lay within circle
	
	double t = omp_get_wtime(); //start time
	#pragma omp parallel for num_threads(tnum) private(x,y) reduction(+:N)
	for(int i=0; i < iter_num; i++)
		{
//		Circle equation : (x-50)^2 + (y-50)^2 = 50^2
		x = rand()%100 - 50;
		y = rand()%100 - 50;
		//printf("%d\t%d\n",x,y);
		if(x*x + y*y <= 2500)
			N++;
		}
	t = omp_get_wtime() - t; //time taken = end time - start time
	printf("%.4f\t",t); //output time taken, precision of 4 decimal places
	
	//printf("%d",N);
	//float PI = (float)(4*N) / (iter_num);
	//printf("\nPI = %.4f\n",PI);
	}

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("Invalid number of arguments. exiting...\n");
		return 1;
		}
	int N = atoi(argv[1]), tnum = atoi(argv[2]);
	//printf("%d\t%d\n",N, tnum);
	process(N,tnum);
	return 0;
}
