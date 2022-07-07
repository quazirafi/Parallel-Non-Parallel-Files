#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */
/* { dg-options "-O2 -fopenmp -fdump-tree-ssa" } */

extern void bar(int);

void foo (void)
{
  int i;

dummyMethod1();
  #pragma omp parallel for schedule (nonmonotonic : dynamic, 4)
  for (i = 0; i < 37; ++i)
    bar(i);
}
dummyMethod2();

/* { dg-final { scan-tree-dump-times "GOMP_parallel_loop_nonmonotonic_dynamic" 1 "ssa" } } */
/* { dg-final { scan-tree-dump-times "GOMP_loop_nonmonotonic_dynamic_start" 0 "ssa" } } */
/* { dg-final { scan-tree-dump-times "GOMP_loop_nonmonotonic_dynamic_next" 2 "ssa" } } */
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