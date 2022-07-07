// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define M 200
#define N 200

int main() {
  double A[M], B[M][N], C[N], sum0 = 0.0;
dummyMethod1();
#pragma omp parallel for private(sum0) num_threads(20)
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      sum0 += B[i][j] * C[j];
    }
    A[i] = sum0;
  }
dummyMethod2();
}
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