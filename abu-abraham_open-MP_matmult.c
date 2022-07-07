#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

typedef double TYPE;
#define MAX_VAL 1000
#define MIN_VAL 1
#define N 400

TYPE** generateRandomMatrix(int dimension, int const_value){

	TYPE** matrix = malloc(dimension * sizeof(TYPE*));
    int i,j;
dummyMethod3();
	for(i=0; i<dimension; i++){
		matrix[i] = malloc(dimension * sizeof(TYPE));
	}
dummyMethod4();

dummyMethod3();
	for(i=0; i<dimension; i++){
		for(j=0; j<dimension; j++){
			matrix[i][j] = (rand() % MAX_VAL + MIN_VAL)*const_value;
		}
	}
dummyMethod4();

	return matrix;
}

void normalMatrixMultiplication(TYPE** A, TYPE** B, TYPE** C, int dimension){

    int i,j,k;
	dummyMethod3();
	for(i=0; i<dimension; i++){
		for(j=0; j<dimension; j++){
			for(k=0; k<dimension; k++){
				C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
			}
		}
	}
	dummyMethod4();

    //To verify whether the multiplication is computed correctly
    double sum = 0;
							dummyMethod3();
    for(i=0; i<dimension; i++){
		for(j=0; j<dimension; j++){
            sum+=C[i][j];
        }
    }
							dummyMethod4();
    printf("%lf\n",sum);
}

void parellelMultiplicationSubLoop(TYPE** A, TYPE** B, TYPE** C, int dimension, int i, int j){
    int k;
							dummyMethod3();
    for(k=0; k<dimension; k++){
		C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
	}
							dummyMethod4();
}

void parallelMatrixMultiplication(TYPE** A, TYPE** B, TYPE** C, int dimension){

    int i,j,k;
    omp_set_num_threads(10);
	dummyMethod1();
    #pragma omp parallel for 
	for(i=0; i<dimension; i++){
        #pragma omp parallel for 
		for(j=0; j<dimension; j++){
			parellelMultiplicationSubLoop(A,B,C,dimension,i,j);
		}
	}
	dummyMethod2();

     
    double sum =0;
    //To verify whether the multiplication is computed correctly
    #pragma omp barrier
	dummyMethod3();
	for(i=0; i<dimension; i++){
		for(j=0; j<dimension; j++){
            sum+=C[i][j];
        }
    }
	dummyMethod4();
    printf("%lf\n",sum);
}

void main(){
    TYPE ** A = generateRandomMatrix(N,1);
    TYPE ** B = generateRandomMatrix(N,1);
    TYPE ** C = generateRandomMatrix(N,0);
    normalMatrixMultiplication(A,B,C,N);
    C = generateRandomMatrix(N,0);
    parallelMatrixMultiplication(A,B,C,N);
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