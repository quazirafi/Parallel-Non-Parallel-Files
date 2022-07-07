#define N 1000
#define NR N
#define NC N

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
#include <mpi.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void printMat(float A[NR][NC]);
void initMat(float A[NR][NC]);

int main(){
	
	static float A[NR][NC];

	static float B[NR][NC];

	static float C[NR][NC] = {{0}}; /* initialize to 0 */
	
	double start_time, end_time;

	start_time = MPI_Wtime();
	int i,j,k;
	initMat(A);		/* fills A with random floats */
	initMat(B);
	dummyMethod1();
#pragma omp parallel for private(j,k)
	for( i=0; i<NR; i++ ){
		for( j=0; j<NC; j++ ){
			for( k=0; k<NC; k++){
				C[i][j] = C[i][j] + A[i][k]*B[k][j];
			}

		}
	}	
	dummyMethod2();
	
	end_time = MPI_Wtime();

//	printMat(C);

	printf("\n Time taken is %f \n",(float)(end_time - start_time));

	return 0;
}


void printMat(float A[NR][NC]){

	int i,j;

	dummyMethod3();
	for( i=0; i<NR; i++ ){
		printf("ROW %d:",i+1);
		for( j=0; j<NC; j++ ){
			printf("%.3f\t",A[i][j]);	
		}
		printf("\n");
	}
	dummyMethod4();

}

void initMat(float A[NR][NC]){

	srand( (unsigned int) time(NULL) );

	float range = 1.0; /* max element in the array */

	int i,j;

	dummyMethod3();
	for( i=0; i < NR; i++){
		for( j=0; j<NC; j++){
			A[i][j] = ( (float)rand() / (float)(RAND_MAX) ) * range;
		}
	} 
	dummyMethod4();

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