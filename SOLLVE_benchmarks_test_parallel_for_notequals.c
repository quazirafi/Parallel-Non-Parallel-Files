//===--- test_parallel_for_notequals.c -------------------------------===//
//
// OpenMP API Version 5.0 Nov 2018
//
// This test checks the parallel for directive with relational-op "!=".
// The test performs simple operations on an int array which are then
// checked for correctness. 
//
////===----------------------------------------------------------------------===//
#include <assert.h>
#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include "ompvv.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 1024

int test_parallel_for_notequals() {
  OMPVV_INFOMSG("test_parallel_for_notequals");
  int errors = 0;
  int x[N];
  int y[N];
  int z[N];

dummyMethod3();
  for (int i = 0; i < N; i++) {
    x[i] = 1;
    y[i] = i + 1;
    z[i] = 2*(i + 1);
  }
dummyMethod4();

			dummyMethod1();
#pragma omp parallel for num_threads(OMPVV_NUM_THREADS_HOST) shared(x, y, z)
  for (int i = 0; i != N; i++) {
    x[i] += y[i]*z[i];
  }
			dummyMethod2();

			dummyMethod3();
  for (int i = 0; i < N; i++) {
    OMPVV_TEST_AND_SET_VERBOSE(errors, x[i] != 1 + (y[i]*z[i]));
  }
			dummyMethod4();

  return errors;
}


int main() {
  int errors = 0;

  OMPVV_TEST_AND_SET_VERBOSE(errors, test_parallel_for_notequals());

  OMPVV_REPORT_AND_RETURN(errors);
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