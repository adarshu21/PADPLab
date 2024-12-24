Write a MPI program that has a total of 4 processes.  
Process with rank 1,2,3 should send following messages respectively to process of rank 0: HELLO, CSE, RVCE.  

hello.c program contains a simple toy program that makes every process say 'Hello from rank %d'.  

ex5.c contains the required program as per manual.  
Process 0 collects messages from the other processes.  
Processes 1,2,3 send messages to Process 0.  

To compile, type:  
<pre>mpicc ex5.c</pre>  

To run, type:  
<pre>mpirun -np 4 a.out  
IMPORTANT: -np 4 denotes that you create 4 processes.</pre>  

