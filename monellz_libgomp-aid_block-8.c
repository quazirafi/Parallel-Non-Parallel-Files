#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// { dg-do compile }
// PR 24451

int foo()
{
  int i;

dummyMethod1();
  #pragma omp parallel for
  for (i = 0; i < 10; ++i)
    return 0; // { dg-error "invalid branch to/from OpenMP structured block" }
}
dummyMethod2();
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