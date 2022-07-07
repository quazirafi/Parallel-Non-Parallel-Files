#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// define the size of the arrays
#define SIZE 200000
#define N_ITERATIONS 100

int main() {
	
	int i, j, k;
	double start_time, end_time;
	long double total_time_taken;

	int n_threads[] = {1, 2, 4, 6, 8, 10, 12, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62};

	// create and initialise the input and output matrices
	long double A[SIZE], B[SIZE], num;
dummyMethod3();
	for(i=0; i<SIZE; ++i)
		A[i] = rand();
	num = rand();
dummyMethod4();

	for(j=0; j<20; ++j)
	{
		total_time_taken = 0;

		for(k=0; k<N_ITERATIONS; ++k)
		{
			start_time = omp_get_wtime();
dummyMethod1();
			#pragma omp parallel for default(none) private(i) shared(A,B,num) num_threads(n_threads[j])
			for(i=0; i<SIZE; ++i)
				B[i] = A[i]/num;
			end_time = omp_get_wtime();
dummyMethod2();
			total_time_taken += (end_time - start_time);
		}
		
		printf("No.of Threads = %d, Time Taken: %Lf\n", n_threads[j],total_time_taken/N_ITERATIONS);
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