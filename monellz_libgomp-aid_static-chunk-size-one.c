#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */
/* { dg-options "-fopenmp -O2 -fdump-tree-optimized -fno-tree-pre" } */

int
bar ()
{
  int a = 0, i;

dummyMethod1();
#pragma omp parallel for num_threads (3) reduction (+:a) schedule(static, 1)
  for (i = 0; i < 10; i++)
    a += i;

  return a;
dummyMethod2();
}

/* Two phis for reduction, one in loop header, one in loop exit.  One phi for iv
   in loop header.  */
/* { dg-final { scan-tree-dump-times "PHI" 3 "optimized" } } */
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