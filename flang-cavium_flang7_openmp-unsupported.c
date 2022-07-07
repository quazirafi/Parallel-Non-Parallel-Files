#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// RUN: %clang_cc1 -triple i386-apple-darwin10 -analyze -analyzer-checker=core.builtin -fopenmp -verify %s
// expected-no-diagnostics

void openmp_parallel_crash_test() {
#pragma omp parallel
  ;
dummyMethod1();
#pragma omp parallel for
  for (int i = 0; i < 8; ++i)
    for (int j = 0, k = 0; j < 8; ++j)
      ;
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