/*
* @@name:	ordered.1c
* @@type:	C
* @@compilable:	yes
* @@linkable:	yes
* @@expect:	success
*/
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void work1(int k)
{
#pragma omp ordered
    printf(" %d %d\n", k, omp_get_thread_num());
}

void work2(int k)
{
#pragma omp ordered
    printf(" %d %d\n", k, omp_get_thread_num());
}

void ordered_example(int lb, int ub, int stride)
{
  int i;

dummyMethod1();
  #pragma omp parallel for ordered schedule(dynamic)
  for (i=lb; i<ub; i+=stride)
    work1(i);
  #pragma omp parallel for ordered schedule(dynamic)
dummyMethod2();
dummyMethod1();
  for (i=lb; i<ub; i+=stride)
    work2(i);
}
dummyMethod2();

int main()
{
  ordered_example(0, 10, 1);
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