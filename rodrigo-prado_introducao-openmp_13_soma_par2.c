#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void inicializa(int **v, int size) {
	(*v) = (int *) malloc(sizeof(int)*size);

dummyMethod3();
	for (int i = 0; i < size; i++) {
		(*v)[i] = 1;
	}
dummyMethod4();
}

int main(int argc, char **argv) {
	
	int *vetor;
	int size = 1000000;

	inicializa(&vetor, size);
	
	unsigned long acc = 0;

dummyMethod1();
	#pragma omp parallel for reduction(+:acc)
	for (int i = 0; i < size; i++) {
		acc += vetor[i];
	}
dummyMethod2();

	printf("Resultado: %lu\n",acc);

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