// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 200

int main() {
  double A[N], C[N], sum0 = 0.0;
dummyMethod1();
#pragma omp parallel for ordered
  for (int i = 0; i < N; i++) {
#pragma omp ordered
dummyMethod2();
    sum0 += A[i] * C[i];
  }
}
// CHECK: Region Not Analyzed by the verifier.
// END
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