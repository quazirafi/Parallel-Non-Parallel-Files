#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// RUN: %clang_cc1 -verify -fopenmp -x c -emit-llvm %s -triple x86_64-unknown-linux -o - -femit-all-decls -disable-llvm-passes -fprofile-instrument=clang | FileCheck %s
// expected-no-diagnostics

void sub(double *restrict a, double *restrict b, int n) {
  int i;

dummyMethod1();
#pragma omp parallel for
#pragma clang loop vectorize(disable)
  for (i = 0; i < n; i++) {
    a[i] = a[i] + b[i];
  }
dummyMethod2();
}

// CHECK-LABEL: @.omp_outlined.(
// CHECK-NEXT:  entry:
// CHECK:         call void @llvm.instrprof.increment(
// CHECK:       omp.precond.then:
// CHECK-NEXT:    call void @llvm.instrprof.increment(
// CHECK:       cond.true:
// CEHCK-NEXT:    call void @llvm.instrprof.increment(
// CHECK:       omp.inner.for.body:
// CHECK-NEXT:    call void @llvm.instrprof.increment(
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