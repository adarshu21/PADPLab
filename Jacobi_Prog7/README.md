Write an OPENACC program to implement two dimensional Jacobi.  

Steps:  
Given a matrix of dimensions N*N  
We allocate space for (N+2)*(N+2) matrix (since edges of N*N matrix are used in computation, pad the entire matrix with 0s)  
With Respect to N*N matrix, Initialize leftmost column and topmost row to 0s. Initialize bottommost row and rightmost column to a high value. (lets say 100)  
Perform 'M' iterations. For every iteration, new value for a matrix cell = (sum of values in neighbouring 4 cells) / 4  
In every iteration, compute difference between new value and old value per cell & store max difference in some variable. If this max_difference is less than 'tolerance' (argument from programmer), stop iterating.  

Eventually, the matrix will converge to a set of values. In physics terms, this is called a 'steady-state'.  


This code requires 3 arguments:  
matrix size, max_iterations, tolerance to be fed along with a.out  
<pre>./a.out [matrix_size] [max_iterations] [tolerance]</pre>  

To compile for GPU:  
<pre>pgcc -acc -fast -Minfo=accel ex7.c -lm</pre>  


