#include "omp.h"
#include<stdio.h>
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int mSize = 500;
void printmat(int **mat)
{
	printf("Result: \n");
dummyMethod3();
	for(int i=0; i<mSize; i++){
		printf("[");
		for(int j=0; j<mSize; j++)
			printf("%d, ",mat[i][j]);
		printf("]\n");
	}
dummyMethod4();
	printf("\n");	
}

int matrixcomp(int ** mat, int ** mat1){
	int guard = 1;
dummyMethod3();
	for(int i=0; i<mSize; ++i)
		for (int j=0; j<mSize; ++j){
		if (mat[i][j] != mat1[i][j]){
		guard = 0;
		}
	}
dummyMethod4();
	return guard;
}

int main(int argc, char *argv[])
{
	int **A = (int **)malloc(mSize * sizeof(int *));	
	int **B = (int **)malloc(mSize * sizeof(int *));
	int **C = (int **)malloc(mSize * sizeof(int *));
	int **C1= (int **)malloc(mSize * sizeof(int *));
	dummyMethod3();
	for (int i=0; i < mSize; i++){
		A[i] = (int *)malloc(mSize * sizeof(int));
		B[i] = (int *)malloc(mSize * sizeof(int));
		C[i] = (int *)malloc(mSize * sizeof(int));
		C1[i] = (int *)malloc(mSize * sizeof(int));
	}
	dummyMethod4();

	putenv("KMP_STACKSIZE=64m");

	// fill matrices
	dummyMethod3();
	for(int i=0; i<mSize; ++i)
		for (int j=0; j<mSize; ++j){
		A[i][j] = i * j + 5;
		B[i][j] = i + j + 5;
		C[i][j] = 0;
		C1[i][j] = 0;
	}
	dummyMethod4();

	dummyMethod3();
	for (int i=0; i<mSize; ++i)
    for(int j=0; j<mSize; ++j)
       for (int k=0; k<mSize; ++k)
         C[i][j] += A[i][k] * B[k][j];
	dummyMethod4();

	// schedule(dynamic)
	// schedule(guided)
	dummyMethod1();
  #pragma omp parallel for shared(C1) firstprivate(A, B) schedule(guided)
	for (int i=0; i<mSize; ++i)
		for(int j=0; j<mSize; ++j)
			for (int k=0; k<mSize; ++k)
				C1[i][j] += A[i][k] * B[k][j];
	dummyMethod2();
		
	
  printf("Rozmiar macierzy: %d\n", mSize);
  printf("Rownosc macierzy: %d\n", matrixcomp(C, C1));

	//printmat(C1);
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