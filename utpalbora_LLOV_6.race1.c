// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
// Taken from ompVerify, Fig. 1
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 20

int main() {
  int x[N], b[N], L[N][N];
dummyMethod1();
#pragma omp parallel for
  for (int i = 0; i < N; i++) {
    x[i] = b[i];
    for (int j = 0; j < i; j++)
      x[i] = x[i] - L[i][j] * x[j];
    x[i] = x[i] / L[i][i];
  }
dummyMethod2();
}
// CHECK: Data Race detected
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