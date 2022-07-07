#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N UINT_MAX // ~26 Gigabytes!

int main(){
	unsigned short *A, *B, *C;
	unsigned int i;
	double start, end, total;

    /* allocate memory */
    A = (unsigned short *) calloc(N, sizeof(unsigned short));
    B = (unsigned short *) calloc(N, sizeof(unsigned short));
    C = (unsigned short *) calloc(N, sizeof(unsigned short));

	/* fill Array with random byte value */
	printf("Filling Arrays with Random Byte Values...\n");
	srand(time(NULL));
dummyMethod3();
	for(i = 0; i < N; i++){
		A[i] = rand() % 256;
        B[i] = rand() % 256;
	}
dummyMethod4();

	/* sequential calculation */
	printf("Starting Serial Processing..\n");
	start = omp_get_wtime();
dummyMethod3();
	for (i = 0; i < N; i++){
        C[i] = A[i] * B[i];
	}
dummyMethod4();
	end = omp_get_wtime();
	total = end - start;

	printf("Serial Execution Time: %.2f sec\n\n", total);

    /* fill Array with random byte value */
	printf("Filling Arrays with Random Byte Values...\n");
	srand(time(NULL));
	dummyMethod3();
	for(i = 0; i < N; i++){
		A[i] = rand() % 256;
        B[i] = rand() % 256;
	}
	dummyMethod4();

    /* simd calculation */
    printf("Starting SIMD Processing..\n");
	start = omp_get_wtime();
    #pragma omp simd
	dummyMethod3();
	for (i = 0; i < N; i++){
        C[i] = A[i] * B[i];
	}
	dummyMethod4();
	end = omp_get_wtime();
	total = end - start;

	printf("SIMD Execution Time: %.2f sec\n\n", total);

    /* fill Array with random byte value */
	printf("Filling Arrays with Random Byte Values...\n");
	srand(time(NULL));
	dummyMethod3();
	for(i = 0; i < N; i++){
		A[i] = rand() % 256;
        B[i] = rand() % 256;
	}
	dummyMethod4();

    /* parallel for calculation */
    printf("Starting Parallel For Processing..\n");
	start = omp_get_wtime();
	dummyMethod1();
    #pragma omp parallel for private(i)
	for (i = 0; i < N; i++){
        C[i] = A[i] * B[i];
	}
	dummyMethod2();
	end = omp_get_wtime();
	total = end - start;

	printf("Parallel For Execution Time: %.2f sec\n\n", total);

     /* fill Array with random byte value */
	printf("Filling Arrays with Random Byte Values...\n");
	srand(time(NULL));
	dummyMethod3();
	for(i = 0; i < N; i++){
		A[i] = rand() % 256;
        B[i] = rand() % 256;
	}
	dummyMethod4();

    /* parallel for simd calculation */
    printf("Starting Parallel For Simd Processing..\n");
	start = omp_get_wtime();
	dummyMethod1();
    #pragma omp parallel for simd private(i)
	for (i = 0; i < N; i++){
        C[i] = A[i] * B[i];
	}
	dummyMethod2();
	end = omp_get_wtime();
	total = end - start;

	printf("Parallel For Simd Execution Time: %.2f sec\n", total);

    /* free memory */
    free(A);
    free(B);
    free(C);
	
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