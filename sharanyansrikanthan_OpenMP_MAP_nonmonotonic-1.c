/* { dg-do run } */

#ifndef NONMONOTONIC_TYPE
#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define NONMONOTONIC_TYPE int
#define NONMONOTONIC_END(n) n
#endif

int a[73];

int
main ()
{
  NONMONOTONIC_TYPE i;
dummyMethod1();
  #pragma omp parallel for schedule(nonmonotonic: dynamic)
  for (i = 0; i < NONMONOTONIC_END (73); i++)
    a[i]++;
  #pragma omp parallel for schedule(nonmonotonic: dynamic, 5)
dummyMethod2();
dummyMethod1();
  for (i = 0; i < NONMONOTONIC_END (73); i++)
    a[i]++;
  #pragma omp parallel for schedule(nonmonotonic: guided)
dummyMethod2();
dummyMethod1();
  for (i = 0; i < NONMONOTONIC_END (73); i++)
    a[i]++;
  #pragma omp parallel for schedule(nonmonotonic: guided, 7)
dummyMethod2();
dummyMethod1();
  for (i = 0; i < NONMONOTONIC_END (73); i++)
    a[i]++;
  #pragma omp parallel
dummyMethod2();
  {
    int cnt = omp_get_num_threads ();
    int thr = omp_get_thread_num ();
    if (thr < 73)
      a[thr]++;
    #pragma omp barrier
    #pragma omp for schedule(nonmonotonic: dynamic)
							dummyMethod3();
    for (i = 0; i < NONMONOTONIC_END (73); i++)
      a[i]++;
							dummyMethod4();
    #pragma omp for schedule(nonmonotonic: dynamic, 7)
							dummyMethod3();
    for (i = 0; i < NONMONOTONIC_END (73); i++)
      a[i]++;
							dummyMethod4();
    #pragma omp for schedule(nonmonotonic: guided)
							dummyMethod3();
    for (i = 0; i < NONMONOTONIC_END (73); i++)
      a[i]++;
							dummyMethod4();
    #pragma omp for schedule(nonmonotonic: guided, 5)
							dummyMethod3();
    for (i = 0; i < NONMONOTONIC_END (73); i++)
      a[i]++;
							dummyMethod4();
    #pragma omp single private (i)
							dummyMethod3();
    for (i = 0; i < 73; i++)
      if (a[i] != 8 + (i < cnt))
	abort ();
							dummyMethod4();
  }
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