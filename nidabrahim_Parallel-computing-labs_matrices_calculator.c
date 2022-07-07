/*
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


// taille maximum des matrices statiques sur etud avec 48 threads (par défaut)
// #define SIZE 590 
#define SHOWSIZE 10 

#define DUMP(flux, ch, x) fprintf(flux, "%s %s\n", ch, #x);
  
void showMatrice(double **A, int n)
{
	int i, j;
	int mytid=-1, nb_ths=0;
	
dummyMethod3();
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++)
			printf("%6.2f%c", A[i][j], ((j+1)%SHOWSIZE) ? '\t' : '\n');  
		printf("\n");  
	}
dummyMethod4();
}


double ** allocMatrice(int n)
{
	double **M=NULL;
	int i, j;

	M = (double **)malloc(n * sizeof(double *));
	if (M) {
			dummyMethod3();
		for (i=0; i<n; i++) {
			M[i] = (double *)malloc(n * sizeof(double)); 
			if (!(M[i])) {
				for (j=i-1; j>=0; j--) free(M[j]);
				free(M);
				M = NULL;
				break;
			}
		}
			dummyMethod4();
	}

	return M;
}

double ** freeMatrice(double **A, int n)
{
	int i;

	dummyMethod3();
	for (i=n-1; i>=0; i--)
		free(A[i]);
	dummyMethod4();
	free(A);
	A = NULL;

	return A;
}

int main(int argc, char **argv)
{
	double **A=NULL, **B=NULL, **C=NULL;

	int i, j, k;
	
	double tstart=0., texec=0.;

	int SIZE=100;

	if (argc > 1) SIZE = atoi(argv[1]);

	/* Allocation de 3 matrices */
	A=allocMatrice(SIZE);	
	if (A) {
		B=allocMatrice(SIZE);	
		if (B) C=allocMatrice(SIZE);
		else A=freeMatrice(A, SIZE);
	}
	if (!C) {
		B = freeMatrice(B, SIZE);
		A = freeMatrice(A, SIZE);

		return -1;
	}

	tstart = omp_get_wtime();
	#pragma omp parallel default(shared) private(i,j,k)
	{
		//printf("Initialisation des matrices ...\n");
			dummyMethod1();
		#pragma omp parallel for shared(A, B) private(i,j)
		for (i=0; i<SIZE; i++) {
			for (j=0; j<SIZE; j++) {
				A[i][j] = i*SIZE+j; 
				B[i][j] = i+j; 
			}
		}
			dummyMethod2();

		//printf("Calcul de la matrice C=A*B ...\n");
			dummyMethod1();
		#pragma omp parallel for shared(A, B, C) private(i,j,k)
		for (i=0; i<SIZE; i++) 
			for (j=0; j<SIZE; j++) {
				C[i][j] = 0;
				for (k=0; k<SIZE; k++)
					C[i][j] += A[i][k] * B[k][j];
			}
			dummyMethod2();
		
	}
	
	texec = omp_get_wtime() - tstart;
	printf("Execution time: %f\n", texec);

	DUMP(stdout, "Show Matrice", C);  
	//showMatrice(C, SIZE);

	// Liberation de memoire
	C = freeMatrice(C, SIZE);
	B = freeMatrice(B, SIZE);
	A = freeMatrice(A, SIZE);

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