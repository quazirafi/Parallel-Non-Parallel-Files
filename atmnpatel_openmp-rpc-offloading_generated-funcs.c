#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// Check that the CHECK lines are generated for clang-generated functions
// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -fopenmp %s -emit-llvm -o - | FileCheck --check-prefix=OMP %s
// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu %s -emit-llvm -o - | FileCheck --check-prefix=NOOMP %s

const int size = 1024 * 1024 * 32;

double A[size];

void foo(void);

int main() {
  int i = 0;

dummyMethod1();
#pragma omp parallel for
  for (i = 0; i < size; ++i) {
    A[i] = 0.0;
  }
dummyMethod2();

  foo();

  return 0;
}

void foo(void) {
  int i = 0;

dummyMethod1();
#pragma omp parallel for
  for (i = 0; i < size; ++i) {
    A[i] = 1.0;
  }
dummyMethod2();
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