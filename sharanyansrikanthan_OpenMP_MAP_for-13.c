#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// At one point in development, a typo disabled the remapping of the
// for iteration variable as private.

// { dg-do compile }
// { dg-options "-fopenmp -fdump-tree-ompexp" }

extern void bar(int);
void foo(void)
{
  int i;

dummyMethod1();
#pragma omp parallel for default(none)
  for (i = 0; i < 10; i++)
    bar(i);
}
dummyMethod2();

// { dg-final { scan-tree-dump-times "omp_data_o" 0 "ompexp" } }
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