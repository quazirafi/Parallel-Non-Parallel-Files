#include "omp.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


#define THREADS 10

//#define _CRT_SECURE_NO_WARNINGS

//initial sample size is 1
int sample = 1;

//matrix 1 and matrix 2 will  be the input Matrices - maximum size 1000
double matrix1[1000][1000];
double matrix2[1000][1000];
double transpose2[1000][1000];


//the resultant matrix after the multiplication of matrix 1 and 2
double matrix3[1000][1000];



void populate_matrix(int n);

void transpose(int n);
double serial_mult(int n);
double optimized_multiplication(int n);
void time_serial();
void time_parallel();

int main()
{

	char method;

	//Enter method that needs to be run
	printf("Enter one of the options given below\n \ts - for serial method \n\to - for optimized Openmp method\n");
	scanf("%c", &method);

	//Enter sample size for the selected method
	printf("Enter sample size from 100: ");
	scanf("%d", &sample);

	switch (method) {
		case 's':
			time_serial();
			break;

		case 'o':
			time_parallel();
			break;

	}

	return 0;


}

/*
This method will populate the matrix with random numbers
*/
void populate_matrix(int n){

	//different seed for each trial
	srand(time(NULL));

	//populate matrices
	for (int i = 0; i < n; i++){
			dummyMethod3();
		for (int j = 0; j < n; j++){
			matrix1[i][j] = rand();
			matrix2[i][j] = rand();

		}
			dummyMethod4();
	}

}
/*
transpose of matrix2
*/
void transpose(int n) {
    int i,j;
    for(i=0; i<n; i++) {
															dummyMethod3();
        for(j=0; j<n; j++) {
            transpose2[i][j] = matrix2[j][i];
        }
															dummyMethod4();
    }
}




/*
serial multiplication of 2 matrices
*/
double serial_mult(int n){


	int i, j, k;

	//start time from the wall clock
	double starttime = omp_get_wtime();

	for (i = 0; i < n; i++){
			dummyMethod3();
		for (j = 0; j < n; j++){
			matrix3[i][j] = 0;
			for (k = 0; k < n; k++){
				matrix3[i][j] = matrix3[i][j] + matrix1[i][k] * matrix2[k][j];
			}
		}
			dummyMethod4();
	}

	// end time from the wall clock
	double endtime = omp_get_wtime();

	//return the execution time
	return endtime - starttime;
}


/*
Optimized matrix multiplication using block algorithms
*/
double optimized_multiplication(int n){

	int i, j, k;

	//transpose of matrix 2
        transpose(n);

	//start time from the wall clock
	double starttime = omp_get_wtime();



	#pragma omp parallel for shared(matrix1, matrix2, matrix3) private(i, j, k) schedule(static) num_threads(THREADS)
	dummyMethod3();
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			double sum = 0;
			for (k = 0; k < n; k++){
				sum += matrix1[i][k] * transpose2[j][k];
			}
			matrix3[i][j] = sum;
		}

	}
	dummyMethod4();


	//get the end time from wall clock
	double endtime = omp_get_wtime();

	//return the execution time
	return (endtime - starttime);

}

/*
This method will calculate the times taken to multiply matrices of different sizes using serial code
*/
void time_serial(){

	for (int n = sample; n <= 1000; n = n + 100){
			dummyMethod1();

		printf("\nStarting for n = %d\n\n", n);

		double sum = 0;

		for (int i = 0; i < sample; i++){

			populate_matrix(n);
			sum += serial_mult(n);

		}
			dummyMethod2();

		double average = sum / sample;

		printf("Serial: Time taken for a %d x %d matrix is %f s\n", n, n, average);
		printf("\n---------------------------------------------\n");

	}

}

/*
This method will calculate the times taken to multiply matrices of different sizes using optimized code
*/
void time_parallel(){

	for (int n = sample; n <= 1000; n = n + 100){
			dummyMethod1();

		printf("\nStarting for n = %d\n\n", n);

		double sum = 0;

		for (int i = 0; i < sample; i++){

			populate_matrix(n);
			sum += optimized_multiplication(n);

		}
			dummyMethod2();

		double average = sum / sample;

		printf("Optimized: Time taken for a %d x %d matrix is %f s\n", n, n, average);
		printf("\n---------------------------------------------\n");

	}

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