1a 
gcc -fopenmp ex1.c 
./a.out 4 1000
1b
mpicc ex1b.c
mpirun -np 3 a.out 1000

2
gcc -fopenmp ex2.c 
/a.out 3 10000

3
gcc -fopenmp ex3.c -lm
./a.out 1000000

5
mpicc ex5.c
mpirun -np 4 a.out

6
gcc -fopenmp ex6.c 
/a.out 1 Passage.txt

7
cc -openmp ex7.c
./a.out [matrix_size] [max_iterations] [tolerance]
