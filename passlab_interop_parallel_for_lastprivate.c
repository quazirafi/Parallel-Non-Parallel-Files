#include <stdio.h>
#include <math.h>
#include "omp_testsuite.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int
check_parallel_for_lastprivate (FILE * logFile)
{
  int sum = 0;
  /*int sum0=0; */
  int known_sum;
  int i;
  int i0 = -1;
dummyMethod1();
#pragma omp parallel for reduction(+:sum) schedule(static,7) lastprivate(i0)
  for (i = 1; i <= LOOPCOUNT; i++)
    {
      sum = sum + i;
      i0 = i;
    }				/*end of for */
  /* end of parallel */
dummyMethod2();
  known_sum = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2;
  return ((known_sum == sum) && (i0 == LOOPCOUNT));
}				/* end of check_parallel_for_lastprivate */

int
crosscheck_parallel_for_lastprivate (FILE * logFile)
{
  int sum = 0;
  /*int sum0=0; */
  int known_sum;
  int i;
  int i0 = -1;
			dummyMethod1();
#pragma omp parallel for reduction(+:sum) schedule(static,7) private(i0)
  for (i = 1; i <= LOOPCOUNT; i++)
    {
      sum = sum + i;
      i0 = i;
    }				/*end of for */
			dummyMethod2();
  /* end of parallel */
  known_sum = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2;
  return ((known_sum == sum) && (i0 == LOOPCOUNT));
}				/* end of check_parallel_for_lastprivate */
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