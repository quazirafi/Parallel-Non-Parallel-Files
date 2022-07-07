// RUN: %libomp-compile-and-run
#include <stdio.h>
#include "omp_testsuite.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int test_omp_parallel_for_firstprivate()
{
  int sum ;
  int i2;
  int i;
  int known_sum;

  sum=0;
  i2=3;

dummyMethod1();
  #pragma omp parallel for reduction(+:sum) private(i) firstprivate(i2)
  for (i = 1; i <= LOOPCOUNT; i++) {
    sum = sum + (i + i2);
  }
dummyMethod2();

  known_sum = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2 + i2 * LOOPCOUNT;
  return (known_sum == sum);
} /* end of check_parallel_for_fistprivate */

int main()
{
  int i;
  int num_failed=0;

dummyMethod3();
  for(i = 0; i < REPETITIONS; i++) {
    if(!test_omp_parallel_for_firstprivate()) {
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