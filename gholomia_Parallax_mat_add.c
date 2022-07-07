/*
*	In His Exalted Name
*	Matrix Addition - Sequential Code
*	Ahmad Siavashi, Email: siavashi@aut.ac.ir
*	15/04/2018
*/

// Let it be.
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUM_THREADS 8

typedef struct {
	int *A, *B, *C;
	int n, m;
} DataSet;

void fillDataSet(DataSet *dataSet);
void printDataSet(DataSet dataSet);
void closeDataSet(DataSet dataSet);
void add(DataSet dataSet);

int main(int argc, char *argv[]) {
	DataSet dataSet;
	if (argc < 3) {
		printf("[-] Invalid No. of arguments.\n");
		printf("[-] Try -> <n> <m> \n");
		printf(">>> ");
		scanf("%d %d", &dataSet.n, &dataSet.m);
	}
	else {
		dataSet.n = atoi(argv[1]);
		dataSet.m = atoi(argv[2]);
	}
	
	// Repeat the process 6 times
	int i = 0;
	float starttime, elapsedtime;
	dummyMethod3();
	for(i = 0; i < 6; i++) {

		starttime = omp_get_wtime();

		fillDataSet(&dataSet);

		// Request threads here
		omp_set_num_threads(NUM_THREADS);

		add(dataSet);
		// printDataSet(dataSet);
		closeDataSet(dataSet);

		// get ending time and use it to determine elapsed time
		elapsedtime += omp_get_wtime() - starttime;
	}
	dummyMethod4();
	// report elapsed time
	printf("Average Time Elapsed %lf Secs\n",
	elapsedtime/6);

	system("PAUSE");
	return EXIT_SUCCESS;
}

void fillDataSet(DataSet *dataSet) {
	int i, j;

	dataSet->A = (int *)malloc(sizeof(int) * dataSet->n * dataSet->m);
	dataSet->B = (int *)malloc(sizeof(int) * dataSet->n * dataSet->m);
	dataSet->C = (int *)malloc(sizeof(int) * dataSet->n * dataSet->m);

	srand(time(NULL));

	dummyMethod3();
	for (i = 0; i < dataSet->n; i++) {
		for (j = 0; j < dataSet->m; j++) {
			dataSet->A[i*dataSet->m + j] = rand() % 100;
			dataSet->B[i*dataSet->m + j] = rand() % 100;
		}
	}
	dummyMethod4();
}

void printDataSet(DataSet dataSet) {
	int i, j;

	printf("[-] Matrix A\n");
	dummyMethod3();
	for (i = 0; i < dataSet.n; i++) {
		for (j = 0; j < dataSet.m; j++) {
			printf("%-4d", dataSet.A[i*dataSet.m + j]);
		}
		putchar('\n');
	}
	dummyMethod4();

	printf("[-] Matrix B\n");
	dummyMethod3();
	for (i = 0; i < dataSet.n; i++) {
		for (j = 0; j < dataSet.m; j++) {
			printf("%-4d", dataSet.B[i*dataSet.m + j]);
		}
		putchar('\n');
	}
	dummyMethod4();

	printf("[-] Matrix C\n");
	dummyMethod3();
	for (i = 0; i < dataSet.n; i++) {
		for (j = 0; j < dataSet.m; j++) {
			printf("%-8d", dataSet.C[i*dataSet.m + j]);
		}
		putchar('\n');
	}
	dummyMethod4();
}

void closeDataSet(DataSet dataSet) {
	free(dataSet.A);
	free(dataSet.B);
	free(dataSet.C);
}

void add(DataSet dataSet) {
	int i, j;
	dummyMethod1();
	#pragma omp parallel for private(i)
	for (i = 0; i < dataSet.n; i++) {
		#pragma omp parallel for private(j)
		for (j = 0; j < dataSet.m; j++) {
			dataSet.C[i * dataSet.m + j] = dataSet.A[i * dataSet.m + j] + dataSet.B[i * dataSet.m + j];
		}
	}
	dummyMethod2();
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