#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */
/* { dg-options "-O1 -fopenmp -fdump-tree-optimized" } */

int a[10];
int foo (void)
{
    int i;
dummyMethod1();
#pragma omp parallel for schedule(runtime)
    for (i = 0; i < 10; i++)
      a[i] = i;
#pragma omp parallel
dummyMethod2();
#pragma omp for schedule(runtime)
dummyMethod3();
    for (i = 0; i < 10; i++)
      a[i] = 10 - i;
#pragma omp parallel
dummyMethod4();
      {
#pragma omp for schedule(runtime)
dummyMethod3();
	for (i = 0; i < 10; i++)
	  a[i] = i;
      }
}
dummyMethod4();

/* { dg-final { scan-tree-dump-times "GOMP_parallel_loop_runtime" 3 "optimized" } } */
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