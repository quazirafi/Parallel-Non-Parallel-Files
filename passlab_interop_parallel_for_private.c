#include <stdio.h>
#include <math.h>
#include "omp_testsuite.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*! Utility function to spend some time in a loop */
static void
do_some_work2 ()
{
  int i;
  double sum = 0;
dummyMethod3();
  for (i = 0; i < 1000; i++)
    {
      sum += sqrt (i);
    }
}
dummyMethod4();

int
check_parallel_for_private (FILE * logFile)
{
  int sum = 0;
  /*int sum0=0; */
  int known_sum;
  int i, i2;
dummyMethod1();
#pragma omp parallel for reduction(+:sum) private(i2) schedule(static,1)
  for (i = 1; i <= LOOPCOUNT; i++)
    {
      i2 = i;
#pragma omp flush
dummyMethod2();
      do_some_work2 ();
#pragma omp flush
      sum = sum + i2;
    }				/*end of for */

  known_sum = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2;
  return (known_sum == sum);
}				/* end of check_paralel_for_private */

int
crosscheck_parallel_for_private (FILE * logFile)
{
  int sum = 0;
  /*int sum0=0; */
  int known_sum;
  int i, i2;
			dummyMethod1();
#pragma omp parallel for reduction(+:sum)  schedule(static,1)
  for (i = 1; i <= LOOPCOUNT; i++)
    {
      i2 = i;
#pragma omp flush
      do_some_work2 ();
#pragma omp flush
      sum = sum + i2;
    }				/*end of for */
			dummyMethod2();

  known_sum = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2;
  return (known_sum == sum);
}				/* end of check_paralel_for_private */
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