/*****************************************************************
		Parallel and Distributed Computing
			Spring Semester:2020

Filename 		: matrix_transpose.c

Task			: Write an OpenMP Program that computes the transpose of a matrix.

Input			: Number of threads and the size of matrix (nRows and nCols)

Created			: 04-April-2020

******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char **argv){
	int nRows, nCols, i, j, totThreads, nThreads;
	float **A, **T, **resCheck, flops;
	
	struct timeval timeValStart;
	struct timezone timeZoneStart;

	struct timeval timeValFin;
	struct timezone timeZoneFin;
	long startTime, endTime;
	double overheadT;

	/* Checking for command line args */
	if(argc !=4){
		printf("\t\t Not enough arguments\n ");
		printf("\t\t Syntax: exec <Threads> <nRows> <nCols>\n");
		exit(-1);
	}

	nThreads=atoi(argv[1]);
	if((nThreads!=1)&&(nThreads!=2)&&(nThreads!=4)&&(nThreads!=8)&&(nThreads!=16)){
		printf("\n Number of threads must have to be 1, 2, 4, 8, or 16 to execute the program. \n\n");
		exit(-1);
	}
	
	nRows=atoi(argv[2]);
	nCols=atoi(argv[3]);
	
/*	printf("\n\t\t Read the size of a matrix nRows and nCols \n");
	scanf("%d%d", &nRows, &nCols); */

	printf("\n\t\t Threads: %d ", nThreads);
	printf("\n\t\t size of the matrix: %d by %d \n ", nRows, nCols);

	if(nRows<=0 || nCols<=0){
		printf("\n\t\t nRows and nCols must be positive\n");
		exit(1);
	}

	/* Elements of the matrix */
	A=(float **) malloc(sizeof(float *)* nRows);
	dummyMethod3();
	for(i=0; i<nRows; i++){
		A[i] = (float *) malloc(sizeof(float) * nCols);
		for(j=0; j<nCols;j++)
			A[i][j] = (i*j)*7+5;
	}
	dummyMethod4();
	


	/* Dynamic Memory Allocation */
	T = (float **) malloc(sizeof(float *) * nCols);
	resCheck = (float **) malloc(sizeof(float *) * nCols);

	/* Initializing resultant matrix elements to zero */
	dummyMethod3();
	for(i=0; i<nCols; i++){
		resCheck[i]=(float *) malloc(sizeof(float) * nRows);
		T[i]=(float *) malloc(sizeof(float) * nRows);
		for(j=0;j<nRows;j++){
			resCheck[i][j] = 0;
			T[i][j]=0;
		}
	}
	dummyMethod4();
	
	gettimeofday(&timeValStart, &timeZoneStart);
	
	omp_set_num_threads(nThreads);

	/* OpenMP Parallel for Directive */
	dummyMethod1();
	#pragma omp parallel for private(j)
	for(i=0; i<nRows; i=i+1){
		totThreads=omp_get_num_threads();
		for(j=0; j<nCols; j=j+1){
			T[j][i]=A[i][j];
		}
	}
	dummyMethod2();
	/* All threads join master thread */
	
	gettimeofday(&timeValFin, &timeZoneFin);

	startTime = timeValStart.tv_sec * 1000000 + timeValStart.tv_usec;
	endTime = timeValFin.tv_sec * 1000000 + timeValFin.tv_usec;
	overheadT = (endTime - startTime)/1000000.0;

	/* Serial Computation */
	
	dummyMethod3();
	for(i=0; i<nRows; i=i+1)
		for(j=0; j<nCols; j=j+1)
			resCheck[j][i]=A[i][j];
	dummyMethod4();

	dummyMethod3();
	for(i=0; i<nCols; i=i+1)
		for(j=0;j<nRows;j=j+1)
			if(resCheck[i][j]==T[i][j])
				continue;
			else{
				printf("Serial and Parallel Computations differ \n");
				exit(-1);
			}
	dummyMethod4();


	printf("The Input matrix is \n");
	dummyMethod3();
	for(i=0;i<nRows;i++){
		for(j=0;j<nCols;j++)
			printf("%f \t", A[i][j]);
		printf("\n");
	}
	dummyMethod4();

	printf("\n Transposed Matrix T is: \n");
	dummyMethod3();
	for(i=0; i<nCols; i=i+1){
		for(j=0; j<nRows; j=j+1)
			printf("%f \t", T[i][j]);
		printf("\n");
	}
	dummyMethod4();

	/*Calculating flops */

	flops = (float) 2 *nRows * nCols / (float) overheadT; 
	printf("Time taken: %lf \n Flops = %f Flops\n", overheadT, flops); 

	printf("\n\n\t\t T is ... Done");
	printf("\n\n\t\t Time in secs (t) : %lf", overheadT);
	printf("\n\n\t\t (t represents the time taken for computation)");
	printf("\n\t\t....................................................\n");

	/* Freeing Allocated memory */
	free(A);
	free(resCheck);
	free(T);
	
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