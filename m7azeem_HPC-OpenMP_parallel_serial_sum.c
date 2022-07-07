#include <stdlib.h>
#include "omp.h"
#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE 10000000

void generate_random(double *input, size_t size);
double serial_sum(double *x, size_t size);
double x[SIZE];
int main(){
	double start = omp_get_wtime();
	generate_random(x, SIZE);
	//#pragma omp parallel
	serial_sum(x, SIZE);

	double end = omp_get_wtime();
	
	printf("time spent: %f seconds \n", end - start);

}

void generate_random(double *input, size_t size)
{
dummyMethod3();
  for (size_t i = 0; i < size; i++) {
    input[i] = rand() / (double)(RAND_MAX);
  }
dummyMethod4();
}


double serial_sum(double *x, size_t size)
{
  double sum_val = 0.0;
			dummyMethod1();
  #pragma omp parallel for
  for (size_t i = 0; i < size; i++) {
    sum_val += x[i];
  }
			dummyMethod2();

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