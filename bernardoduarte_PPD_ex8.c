#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include "timer.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char const *argv[])
{
	int i = 0;
	int j = 0;
	int count1 = 0;
	int pc = 0;
	int N;
	int T;
	double tempo;
	double fim;
	double inicio;
	N = atoi(argv[1]);
	T = atoi(argv[2]);
	printf("N=%d\nT=%d\n", N, T);

	GET_TIME(inicio);

	dummyMethod1();
	#pragma omp parallel for reduction(+:pc) num_threads(T) private(count1,i,j)
	for (i = 2; i <= N; ++i) {
		int count1 = 0;
		for (j = 1; j <= i; ++j) {
			if ((i % j) == 0) {
				count1++;
			}
		}
		if (count1 == 2) {
			pc++;
		}
	}
	dummyMethod2();

	GET_TIME(fim);
	tempo = fim - inicio;

	printf("Tempo: %.8lf\n", tempo);
	printf("PRIMOS: %d\n", pc);

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