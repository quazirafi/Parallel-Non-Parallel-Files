// RUN: %libomp-compile-and-run
#include <stdio.h>
#include <math.h>
#include "omp_testsuite.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int test_omp_parallel_for_if()
{
  int known_sum;
  int num_threads;
  int sum, sum2;
  int i;
  int control;

  control = 0;
  num_threads=0;
  sum = 0;
  sum2 = 0;

dummyMethod1();
  #pragma omp parallel for private(i) if (control==1)
  for (i=0; i <= LOOPCOUNT; i++) {
    num_threads = omp_get_num_threads();
    sum = sum + i;
  }
dummyMethod2();

  known_sum = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2;
  fprintf(stderr, "Number of threads determined by"
    " omp_get_num_threads: %d\n", num_threads);
  return (known_sum == sum && num_threads == 1);
} /* end of check_parallel_for_private */

int main()
{
  int i;
  int num_failed=0;

			dummyMethod3();
  for(i = 0; i < REPETITIONS; i++) {
    if(!test_omp_parallel_for_if()) {
      num_failed++;
    }
  }
			dummyMethod4();
  return num_failed;
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