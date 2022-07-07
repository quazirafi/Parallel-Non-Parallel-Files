// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 200

int main() {
  int A[N], x = 0;
dummyMethod1();
#pragma omp parallel for linear(x : 2)
  for (int i = 0; i < N; i++)
    A[i] = x;
}
dummyMethod2();
// CHECK: Region is Data Race Free.
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