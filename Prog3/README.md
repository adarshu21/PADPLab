Implement Sieve of Eratosthenes to find all prime numbers up to N (input).

Implement cache-unfriendly and cache-friendly versions, compare performance.
Parallelize cache-friendly version, compare performance.


Sieve of Eratosthenes:
Load all numbers from 2 to N.
Delegate starting number of array as 'p'. 
In increments of 'p', mark off the numbers.
The next smallest number remaining in array is the new 'p' (next smallest prime).
Repeat till you can't find any new 'p', i.e. can't find next smallest prime any more.

Example:
2 3 4 5 6 7 8 9.  		p = 2
In run 1: eliminate 4 6 8. 	p = 3
In run 2: eliminate 6 9.	p = 5
In run 3: no elims		p = 7
In run 4: no elims. 		END


Method followed:
Given number N. (Find all primes upto N)
Find all primes using Sieve of Eratosthenes method mentioned above from 1 to root(N).
Now, split the remaining numbers from root(N) to N into segments. 
Eg) split as: root(N)+1 to 2*root(N), 2*root(N)+1 to 3*root(N) and so on...
Use the primes computed from 1 to root(N) to filter out all composite numbers present in the segments.
The numbers that still remain will be primes.

To run:
./a.out {enter number here}
