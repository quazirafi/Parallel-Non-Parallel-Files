#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char **argv) {
	// quantos numeros primos entre 1 e N ?
	
	unsigned long n = 99999;
	unsigned long aux = 2;

	unsigned long primes = 0;
	
dummyMethod1();
	#pragma omp parallel for firstprivate(aux) reduction(+:primes) schedule(guided)
	for (unsigned long i = 2; i < n; i++) {
		
		while (aux < i) {
			if (i % aux == 0) break;
			aux++;
		}
		
		if (aux == i) primes++;

		aux = 2;	
	}
dummyMethod2();

	printf("%lu primos entre 1 e %lu\n",primes,n);

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