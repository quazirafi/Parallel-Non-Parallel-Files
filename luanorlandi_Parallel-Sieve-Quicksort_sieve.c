// compile with
// gcc -g -Wall -fopenmp -o sieve sieve.c -lm

// run with
// ./sieve n numero_threads
// onde n eh um intervalo de [0...n]


/*
 * Integrantes:
 * Marcos Vinicius Barros L. A. J.			8922393
 * Luan Gustavo Orlandi						8531532
 * Leonardo Mellin Moreira Ferreira			7982767
*/




#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define PRIME 0
#define NONPRIME 1

#define THREAD_COUNT 7

/* typedef for  max range of a integer */
typedef unsigned long long int slli;

void crossout(slli *prime, slli size, int nthreads) {

	slli i, j;
	dummyMethod1();
	#pragma omp parallel for num_threads(nthreads) \
		private(j)
	for(i = 2; i < size; i++) {
		/* if is crossout, all his multiple
			it's already or being crossout */
		if(prime[i] == PRIME) {
			for(j = i+i; j < size; j += i) {
				prime[j] = NONPRIME;
			}
		}
	}
	dummyMethod2();
}

void showAnswer(slli *prime, slli size) {

	slli total = 0, i;

	printf("Prime numbers found (2 to %lld):\n", size-1);

	dummyMethod3();
	for(i = 2; i < size; i++) {
		if(prime[i] == PRIME) {
			printf("%lld ", i);
			total++;
		}
	}
	dummyMethod4();

	printf("\nTotal: %lld\n", total);
}

int main(int argc, char *argv[]) {

	slli *prime;		/* boolean */
	slli size;
	int nthreads = 0;
	clock_t t;

	if(argc < 3) {
		printf("Need argument for range (r) and numbers of threads(n) ex: ./sieve n r ");
		exit(-1);
	}

	/* inclusive range */
	size = 1 + atol(argv[1]);
	nthreads = atoi(argv[2]);

	/* prime numbers will be 0 */
	/* not prime numbers will be 1 */
	prime = (slli *) calloc(size, sizeof(slli));

	t = clock();

	/* put 1 in not primes */
	crossout(prime, size, nthreads);

	t = clock() - t;

	showAnswer(prime, size);
	printf("Numbers of threads used: %d\n", nthreads);
	printf("Crossout done in %.2lfs\n", (double) t / CLOCKS_PER_SEC);

	free(prime);

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