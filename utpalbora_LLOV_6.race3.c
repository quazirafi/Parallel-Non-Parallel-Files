// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
// Taken from ompVerify, Sec 4.3
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 20

int main() {
  int i, j, A[N], a[N][N], B[N][N];
dummyMethod1();
#pragma omp parallel for private(j)
  for (i = 0; i < N; i++)
    for (j = 0; j < i; j++) {
      A[j] = a[i][j];
      B[i][j] = A[j];
    }
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