#include <stdlib.h>
#include "omp.h"
#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE 10000000

void generate_random(size_t size);
double serial_sum(size_t size);
double x[SIZE];
int main(){
	printf("Start \n");
	double start = omp_get_wtime();
	
	generate_random(SIZE);
	
	serial_sum(SIZE);
	
	double end = omp_get_wtime();
	
	printf("time spent: %f seconds \n", end - start);

}

void generate_random(size_t size)
{
dummyMethod3();
  for (size_t i = 0; i < size; i++) {
    x[i] = rand() / (double)(RAND_MAX);
  }
dummyMethod4();
}


double serial_sum(size_t size)
{
	int MAX_THREADS = omp_get_max_threads();
	double sum[MAX_THREADS];


	#pragma omp parallel shared(sum)
	{
		int thread_id = omp_get_thread_num();
			
			dummyMethod1();
		#pragma omp parallel for
		for (size_t i = 0; i < size; i++) {
			sum[thread_id] += x[i];
		}
			dummyMethod2();

	}

	double sum_val = 0.0;
	dummyMethod3();
	for(size_t l=1; l< MAX_THREADS;l++){
		sum_val += sum[l];
	} 
	dummyMethod4();

  return sum_val;
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