// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
// Taken from ompVerify, Fig. 4
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 20
#define M 20

int main() {
  int uold[N][M], u[N][M];
  int i, j;
  double b = 1.0, omega = 0.8, resid, error = 0.0;
dummyMethod1();
#pragma omp parallel for private(j, resid) reduction(+ : error)
  for (i = 1; i < N; i++) {
    for (j = 1; j < M; j++) {
      resid = (uold[i][j] + uold[i - 1][j] + uold[i + 1][j] + uold[i][j - 1] +
               uold[i][j + 1]) /
              b;
      u[i][j] = uold[i][j] - omega * resid;
      error = error + resid * resid;
    }
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