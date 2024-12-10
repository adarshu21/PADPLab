#!/bin/bash

arr_size=(10 100 500 1000 2000)
num_threads=(1 2 4 8 16)
 
rm output.txt  #remove text file if present

printf "\t" >> output.txt   
for tnum in "${num_threads[@]}"; do
	printf "%d\t" ${tnum} >> output.txt
done
printf "\n" >> output.txt

for N in "${arr_size[@]}"; do
	printf "%d\t" ${N} >> output.txt
	for tnum in "${num_threads[@]}"; do
		./a.out ${N} ${tnum} >> output.txt
	done
	printf "\n" >> output.txt
done

cat output.txt
