#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main() {
	const int DIM = 1000;
	int i,j,k,test;
	double debut, fin, temps;
	double **a, **b, **cresu, **ctest;
	a= (double**) malloc(DIM*sizeof(double*)); b=
	(double**) malloc(DIM*sizeof(double*)); cresu=
	(double**) malloc(DIM*sizeof(double*)); ctest=
	(double**) malloc(DIM*sizeof(double*));
	// initialisations etc...
	
dummyMethod3();
	for (i=0; i<DIM; i++) {
		a[i]=(double*) malloc(DIM*sizeof(double));
		b[i]=(double*) malloc(DIM*sizeof(double));
		cresu[i]=(double*) malloc(DIM*sizeof(double));
		ctest[i]=(double*) malloc(DIM*sizeof(double));
		for (j = 0; j < DIM; j++) {
			a[i][j] = (double)(i-j); b[i][j] =
			(double)(i+j); cresu[i][j] = 0.0;
			ctest[i][j] = 0.0;
		}
	}
dummyMethod4();
	// Multiplication C = A x B (séquentiel)
	printf("Multiplication sequentielle:\n");
	
	debut= omp_get_wtime();
dummyMethod3();
	for (i = 0; i < DIM; i++)
		for (j = 0; j < DIM; j++)
			for (k = 0; k < DIM; k++)
				ctest[i][j] += a[i][k] * b[k][j];
	fin= omp_get_wtime();
dummyMethod4();
	temps=fin-debut;
	printf ("Calcul séquentiel %f secondes\n", temps);
	// Multiplication C = A x B (parallèle)
	omp_set_num_threads(4);
	printf("Multiplication parallelle:\n");
	debut= omp_get_wtime();
	for (i = 0; i < DIM; i++){
		for (j = 0; j < DIM; j++){
							dummyMethod1();
			#pragma omp parallel for schedule(static, 250), reduction(+ \
						                         : test)
				for (k = 0; k < DIM; k++){
					test += a[i][k] * b[k][j];
				}
							dummyMethod2();
			ctest[i][j]=test;			

		}
	}
	fin= omp_get_wtime();
	temps=fin-debut;
	printf ("Calcul parallél %f secondes\n", temps);
	return (0);
	
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