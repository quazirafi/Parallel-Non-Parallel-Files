// RUN: %libomp-compile-and-run
#include <stdio.h>
#include "omp_testsuite.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int test_omp_parallel_for_lastprivate()
{
  int sum;
  int i;
  int i0;
  int known_sum;

  sum =0;
  i0 = -1;

dummyMethod1();
  #pragma omp parallel for reduction(+:sum) \
    schedule(static,7) private(i) lastprivate(i0)
  for (i = 1; i <= LOOPCOUNT; i++) {
    sum = sum + i;
    i0 = i;
  } /* end of parallel for */
dummyMethod2();

  known_sum = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2;
  return ((known_sum == sum) && (i0 == LOOPCOUNT));
} /* end of check_parallel_for_lastprivate */

int main()
{
  int i;
  int num_failed=0;

			dummyMethod3();
  for(i = 0; i < REPETITIONS; i++) {
    if(!test_omp_parallel_for_lastprivate()) {
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