#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -target-cpu x86-64  %s -O3 -opt-record-file=t1.opt -fopenmp -emit-llvm-bc -o %t.bc
// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -target-cpu x86-64 -O3 -x ir %t.bc -opt-record-file %t.opt -fopenmp -emit-obj
// RUN: cat %t.opt |  FileCheck -check-prefix=CHECK  %s
// REQUIRES: x86-registered-target

void foo(int *a, int *b, int *c) {
dummyMethod1();
#pragma omp parallel for
  for (int i = 0; i < 100; i++) {
    a[i] = b[i] + c[i];
  }
dummyMethod2();
}

// CHECK: --- !Missed
// CHECK: Pass:            inline
// CHECK: Name:            NoDefinition
// CHECK: Function:        foo
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