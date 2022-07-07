#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */
/* { dg-options "-O2 -fopenmp -std=c99 -fipa-pta -fdump-tree-optimized" } */

#define N 2

int
foo (void)
{
  int a[N], b[N], c[N];
  int *ap = &a[0];
  int *bp = &b[0];
  int *cp = &c[0];

dummyMethod1();
#pragma omp parallel for
  for (unsigned int idx = 0; idx < N; idx++)
    {
      ap[idx] = 1;
      bp[idx] = 2;
      cp[idx] = ap[idx];
    }

  return *cp;
dummyMethod2();
}

/* { dg-final { scan-tree-dump-times "\\] = 1;" 2 "optimized" } } */
/* { dg-final { scan-tree-dump-times "\\] = 2;" 1 "optimized" } } */
/* { dg-final { scan-tree-dump-times "\\] = _\[0-9\]*;" 0 "optimized" } } */
/* { dg-final { scan-tree-dump-times "\\] = " 3 "optimized" } } */
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