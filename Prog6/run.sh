#!/bin/bash

declare -A my_files
my_files["1.25"]="Passage_1MB.txt"
my_files["2.5"]="Passage_2MB.txt"
my_files["5"]="Passage_5MB.txt"
my_files["10"]="Passage_10MB.txt"

#arr_size=(100 1000 10000 100000 1000000)
keys=("1.25" "2.5" "5" "10")
num_threads=(1 2 4 8)
 
rm output.txt  #remove text file if present

#print first row
printf "\t" >> output.txt   
for tnum in "${num_threads[@]}"; do
	printf "%d\t" ${tnum} >> output.txt
done
printf "\n" >> output.txt

for key in "${keys[@]}"; do
	printf "%s\t" ${key} >> output.txt
	for tnum in "${num_threads[@]}"; do
		./a.out ${my_files[$key]} ${tnum} >> output.txt
	done
	printf "\n" >> output.txt
done

cat output.txt
