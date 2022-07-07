#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// RUN: %clang_cc1 -triple i386-unknown-unknown -fopenmp %s -emit-llvm -o - -disable-llvm-optzns | FileCheck %s

// CHECK: declare !callback ![[cid:[0-9]+]] void @__kmpc_fork_call
// CHECK: declare !callback ![[cid]] void @__kmpc_fork_teams
// CHECK: ![[cid]] = !{![[cidb:[0-9]+]]}
// CHECK: ![[cidb]] = !{i64 2, i64 -1, i64 -1, i1 true}

void work1(int, int);
void work2(int, int);
void work12(int, int);

void foo(int q) {
  int p = 2;

  #pragma omp parallel firstprivate(q, p)
  work1(p, q);

dummyMethod1();
  #pragma omp parallel for firstprivate(p, q)
  for (int i = 0; i < q; i++)
    work2(i, p);

  #pragma omp target teams firstprivate(p)
dummyMethod2();
  work12(p, p);
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