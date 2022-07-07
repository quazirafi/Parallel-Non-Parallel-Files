#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define SIZE 2000

int main(int argc, char **argv)
{
	int res = 0;

	int *matrice_A;
	double t, start, stop;
	// Allocations
	matrice_A = (int *)malloc(SIZE * SIZE * sizeof(int));

	// Initialisations
dummyMethod3();
	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			matrice_A[i * SIZE + j] = 1;
		}
	}
dummyMethod4();
	start = omp_get_wtime();
dummyMethod1();
#pragma omp parallel for reduction (+:res)
		for (int i = 0; i < SIZE; i++){
			for (int j = 0; j < SIZE; j++){
				res += matrice_A[i * SIZE + j];
			}
		}
dummyMethod2();

	stop = omp_get_wtime();
	t = stop - start;
	printf("---Reduction---\n");
	printf("Le resultat: %d, temps: %f\n", res, t);
	// Liberations
	free(matrice_A);

	return EXIT_SUCCESS;
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