// Distributed and parallel technologies, Andrew Beveridge, 03/03/2014
// To Compile:		gcc -Wall -O -o ab-totient-omp -fopenmp ab-totient-omp.c
// To Run / Time:	/usr/bin/time -v ./ab-totient-omp range_start range_end

#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* 	When input is a prime number, the totient is simply the prime number - 1. Totient is always even (except for 1).
	If n is a positive integer, then φ(n) is the number of integers k in the range 1 ≤ k ≤ n for which gcd(n, k) = 1  */
long getTotient (long number) {
	long result = number;

    // Check every prime number below the square root for divisibility
    if(number % 2 == 0){
        result -= result / 2;
        do 
            number /= 2;
        while(number %2 == 0);
    }

    // Primitive replacement for a list of primes, looping through every odd number
    long prime;
dummyMethod3();
	for(prime = 3; prime * prime <= number; prime += 2){
        if(number %prime == 0){
            result -= result / prime;
            do 
                number /= prime;
            while(number % prime == 0);
        }
    }
	
    // Last common factor 
    if(number > 1) 
        result -= result / number;

    // Return the result. 
    return result; 
}
dummyMethod4();

// Main method.
int main(int argc, char ** argv) {
	// Load inputs
	long lower, upper;
	sscanf(argv[1], "%ld", &lower);
	sscanf(argv[2], "%ld", &upper);

	int i; 
	long result = 0.0;
	
	// We know the answer if it's 1; no need to execute the function
	if(lower == 1) {
		result = 1.0;
		lower = 2;
	}
	
	dummyMethod1();
	#pragma omp parallel for default(shared) private(i) schedule(auto) reduction(+:result) num_threads(10)

	// Sum all totients in the specified range
	for (i = lower; i <= upper; i++) {
		result = result + getTotient(i);
	}
	dummyMethod2();
	
	// Print the result
	printf("Sum of Totients between [%ld..%ld] is %ld \n", lower, upper, result);
	
	// A-OK!
	return 0;
}
int dummyMethod1(){
    return 0;
}
int dummyMethod2(){
    return 0;
}
int dummyMethod3(){
    return 0;
}
int dummyMethod4(){
    return 0;
}