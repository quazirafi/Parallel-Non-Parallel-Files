#include <stdio.h>
#include <math.h>
#include "omp_testsuite.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static int last_i = 0;

/*! 
  Utility function: returns true if the passed argument is larger than 
  the argument of the last call of this function.
  */
static int
check_i_islarger2 (int i)
{
  int islarger;
  islarger = (i > last_i);
  last_i = i;
  return (islarger);
}

int
check_parallel_for_ordered (FILE * logFile)
{
  int sum = 0;
  int known_sum;
  int i;
  int is_larger = 1;
  last_i = 0;
			dummyMethod1();
#pragma omp parallel for schedule(static,1) ordered
  for (i = 1; i < 100; i++)
    {
#pragma omp ordered
      {
	is_larger = check_i_islarger2 (i) && is_larger;
	sum = sum + i;
      }
    }
			dummyMethod2();
  known_sum = (99 * 100) / 2;
  return (known_sum == sum) && is_larger;
}

int
crosscheck_parallel_for_ordered (FILE * logFile)
{
  int sum = 0;
  int known_sum;
  int i;
  int is_larger = 1;
  last_i = 0;
			dummyMethod1();
#pragma omp parallel for schedule(static,1)
  for (i = 1; i < 100; i++)
    {

      {
	is_larger = check_i_islarger2 (i) && is_larger;
	sum = sum + i;
      }
    }
			dummyMethod2();
  known_sum = (99 * 100) / 2;
  return (known_sum == sum) && is_larger;
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