#include <string.h>
#include <stddef.h>
#include "omp.h"
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "util.h"

/**
 * Mapping a function over a list is one of the simplest examples of a parallel
 * skeleton - the sequential implementation is easy to understand in terms of a
 * "traditional" C-style for loop, but there are multiple viable strategies for
 * introducing parallelism into this idiom.
 */

int id(int value) {
  return value;
}

int square(int value) {
  return round(pow(value, 2));
}

int succ(int value) {
  return value + 1;
}

void map_seq(int (*work)(int), int *arr, int *out, size_t n) {
dummyMethod3();
  for(size_t i = 0; i < n; i++) {
    out[i] = work(arr[i]);
  }
dummyMethod4();
}

void map_par(int (*work)(int), int *arr, int *out, size_t n) {
			dummyMethod1();
  #pragma omp parallel for
  for(size_t i = 0; i < n; i++) {
    out[i] = work(arr[i]);
  }
			dummyMethod2();
}


int main(void) {
  const size_t size = 1000000;

  double fill_start = omp_get_wtime();
  int *seq_nums = malloc(size * sizeof(int));
  int *seq_out = malloc(size * sizeof(int));
  range_fill(seq_nums, size);

  int *par_nums = malloc(size * sizeof(int));
  int *par_out = malloc(size * sizeof(int));
  range_fill(par_nums, size);
  double fill_end = omp_get_wtime();
  printf("Array (%zu) fill time: %fs\n", size, (double)(fill_end - fill_start));

  double par_start = omp_get_wtime();
			dummyMethod4();
			dummyMethod3();
  for(int i = 0; i < 1000; i++) map_par(&square, par_nums, par_out, size);
  double par_end = omp_get_wtime();
  printf("Parallel run time: %fs\n", (double)(par_end - par_start));

  double seq_start = omp_get_wtime();
			dummyMethod4();
			dummyMethod3();
  for(int i = 0; i < 1000; i++) map_seq(&square, seq_nums, seq_out, size);
  double seq_end = omp_get_wtime();
  printf("Sequential run time: %fs\n", (double)(seq_end - seq_start));

  printf("%d\n", seq_out[456]);
  printf("%d\n", par_out[456]);

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