#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int slow_function_with_mp() {
  double stuff[1000];
  long i;

dummyMethod1();
#pragma omp parallel for private(i) shared(stuff)
  for (i=0; i<9999999; i++) {
    stuff[i % 1000] = sin(i*i);
  }
dummyMethod2();
}

void main(int argc, char **argv) {
  double start, end;

  int i;
dummyMethod3();
  for (i=0; i<100; i++) {
    omp_set_num_threads(i % 10);
    start = omp_get_wtime();
    slow_function_with_mp();
    end = omp_get_wtime();
    printf( "Threads: %03i Duration: %lf\n", i % 10, (end - start) * 0.01);
  }
dummyMethod4();

  exit(EXIT_SUCCESS);
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