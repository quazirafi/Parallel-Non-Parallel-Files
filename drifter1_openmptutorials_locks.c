#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N UINT_MAX

int main(){
	unsigned char *A;
	unsigned int i, count;
	time_t start_t, end_t;
	double total;

	/* allocate memory */
	A = (unsigned char*) malloc(N * sizeof(unsigned char));

	/* fill Array with random byte value */
	printf("Filling Array with Random Vaues...\n");
	srand(time(NULL));
dummyMethod3();
	for(i = 0; i < N; i++){
		A[i] = rand() % 256;
	}
dummyMethod4();

	/* sequential calculation */
	printf("Starting Sequential Calculation...\n");
	count = 0;
	start_t = time(NULL);
dummyMethod3();
	for (i = 0; i < N; i++){
		if(A[i] == 0){
			count++;
		}
	}
dummyMethod4();
	end_t = time(NULL);
	total = difftime(end_t, start_t);

	printf("Sequential Execution Time: %.2f sec, Zeroes in Array: %u or %.2f%%\n",
		total, count, (double)count/UINT_MAX * 100);

	/* initialize lock */
	omp_lock_t lock;
	omp_init_lock(&lock);

	/* parallel calculation */
	printf("Starting Parallel Calculation...\n");
	count = 0;
	start_t = time(NULL);
	dummyMethod1();
	#pragma omp parallel for private(i)
	for (i = 0; i < N; i++){
		if(A[i] == 0){
			omp_set_lock(&lock);
			count++;
			omp_unset_lock(&lock);
		}
	}
	dummyMethod2();
	end_t = time(NULL);
	total = difftime(end_t, start_t);

	printf("Parallel Execution Time: %.2f sec, Zeroes in Array: %u or %.2f%%\n",
		total, count, (double)count/UINT_MAX * 100);

	/* destroy lock */
	omp_destroy_lock(&lock);

	/* free memory */
	free(A);
	
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