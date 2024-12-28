Compute value of PI using Monte Carlo method.  
Tabulate results of parallelization by varying number of iterations and number of threads assigned.  

PI value increases in accuracy with increase in iterations performed.  
Value of 3.14 was achieved by performing 100000 iterations per thread, 4 threads assigned, implying 400000 iterations performed.  

MPI Code also given (as ex1b.c)  

To compile:  
<pre>mpicc ex1b.c</pre>  

To execute:  
<pre>mpirun -np (enter_number_of_processes) a.out (enter_number_of_iterations_per_process)</pre>  
