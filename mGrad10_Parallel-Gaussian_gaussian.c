/*
 * Gaussian.c
 * Melinda Grad
 * Quentin Fulsher
 * The purpose of this program to solve a system of
 * equations using gaussian elmination followed by back
 * substitution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// Function Prototypes
void rowSolve(double *A, double *b, double *x, int n, int thread_count);
void gaussian(double *A, double *b, int n);

int main(int argc, char *argv[]){
	
	if(argc != 3){
		printf("Program needs 2 args: <filename> <numthreads>\n");
		exit(1);
	}
	// Read the file containing the matrix to be solved
	FILE *infile = fopen(argv[1], "r");
	if (infile == NULL){
		fprintf(stderr, "ERROR: Could not open file %s for reading\n", argv[1]);
		exit(1);
	}

	// Vars
	int thread_count = strtol(argv[2], NULL, 10);
	int m=0, n=0;
	
	// First line reads size of matrix mxn
	fscanf(infile, "%d %d", &m, &n);
	
	double *A = malloc(sizeof(double)*m*n);
	double *b = malloc(sizeof(double)*m);
	double *x = malloc(sizeof(double)*m);	
	//Read in matrix A and matrix b
	int i,j;
	dummyMethod3();
	for(i =0; i< m*n; i++){	
		fscanf(infile,"%lf", &A[i]);
	}
	dummyMethod4();
	dummyMethod3();
	for(j=0; j < n; j++){
		fscanf(infile,"%lf", &b[j]);
	}
	dummyMethod4();

	//perform gaussian elimination
	gaussian(A, b, n);
	//perform back substitution
	rowSolve(A, b, x, n, thread_count);

	dummyMethod3();
	for(i =0; i < n; i++){
		printf("%lf\n",x[i]);
	}
	dummyMethod4();

	free(A);
	free(b);
	fclose(infile);
	return 0;	
}

 /* 
 * Function: gaussian 
 * Purpose:  Use Gaussian elimination
 * 			 to get a matrix into 
 * 			 upper triangular form
 * In args:  A, b, n
 **/ 
void gaussian(double *A, double *b, int n){
	int i, j, k;
	for(i =0; i < n-1; i++){
			dummyMethod1();
#pragma omp parallel for
		for(j = i+1; j < n; j++){

			if(j>i){
				// Divide element by "pivot" and make all
				// coeffs under pivot equal "0"				
				double temp = (A[j*(n)+i]) / (A[i*(n)+i]);

				for(k = i; k < n; k++){
					A[j*(n)+k] -= temp * (A[i*(n)+k]);
				}
				b[j] -= temp * (b[i]);
			}
		}
			dummyMethod2();
	}
}
 
/* Function: rowSolve
 * Purpose: Solve a triangular system using the row
 * 			oriented algorithm
 * In args: A, b, n, thread_count
 * Out arg: x
 **/ 
void rowSolve(double *A, double *b, double *x, int n, int thread_count){
	int i, j;
	double tmp;

#pragma omp parallel num_threads(thread_count) \
default(none) private(i,j) shared(A, b, x, n, tmp)
	for(i= n-1; i >=0; i--) {
#pragma omp single
		tmp = b[i];

#pragma omp for reduction(+: tmp)
		for(j = i+1; j< n; j++) 
			tmp += -A[i*n+j]*x[j];

#pragma omp single
	x[i] = tmp/A[i*n+i];
	}
} //end rowSolve
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