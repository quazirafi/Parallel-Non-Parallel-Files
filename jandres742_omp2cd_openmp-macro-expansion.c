#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// RUN:   %clang_cc1 -fopenmp -E -o - %s 2>&1 | FileCheck %s

// This is to make sure the pragma name is not expanded!
#define omp (0xDEADBEEF)

#define N 2
#define M 1
#define E N>

#define map_to_be_expanded(x) map(tofrom:x)
#define sched_to_be_expanded(x,s) schedule(x,s)
#define reda_to_be_expanded(x) reduction(+:x)
#define redb_to_be_expanded(x,op) reduction(op:x)

void foo(int *a, int *b) {
  //CHECK: omp target map(a[0:2]) map(tofrom:b[0:2*1])
  #pragma omp target map(a[0:N]) map_to_be_expanded(b[0:2*M])
  {
    int reda;
    int redb;
    //CHECK: omp parallel for schedule(static,2> >1) reduction(+:reda) reduction(*:redb)
dummyMethod1();
    #pragma omp parallel for sched_to_be_expanded(static, E>1) \
        reda_to_be_expanded(reda) redb_to_be_expanded(redb,*)
    for (int i = 0; i < N; ++i) {
      reda += a[i];
      redb += b[i];
    }
dummyMethod2();
    a[0] = reda;
    b[0] = redb;
  }
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