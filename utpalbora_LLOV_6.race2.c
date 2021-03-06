// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
// Taken from ompVerify, Fig. 2
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 20
#define T 1000

int main() {
  int A[N][N], B[N][N];

  for (int t = 0; t < T; t++)
dummyMethod1();
#pragma omp parallel for
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        A[i][j] =
            (B[i][j] + A[i - 1][j] + B[i + 1][j] + B[i][j - 1] + B[i][j + 1]) *
            0.2;
}
dummyMethod2();
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