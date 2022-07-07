#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// RUN: %libomp-compile-and-run

/*
Bugzilla: https://bugs.llvm.org/show_bug.cgi?id=36720

Assertion failure at kmp_runtime.cpp(1715): nthreads > 0.
OMP: Error #13: Assertion failure at kmp_runtime.cpp(1715).

The assertion fails even with OMP_NUM_THREADS=1. If the second task is removed,
everything runs to completion. If the "omp parallel for" directives are removed
from inside the tasks, once again everything runs fine.
*/

#define N 1024

int main() {
  #pragma omp task
  {
    int i;
dummyMethod1();
    #pragma omp parallel for
    for (i = 0; i < N; i++)
      (void)0;
  }
dummyMethod2();

  #pragma omp task
  {
    int i;
dummyMethod1();
    #pragma omp parallel for
    for (i = 0; i < N; ++i)
      (void)0;
  }
dummyMethod2();

  #pragma omp taskwait

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