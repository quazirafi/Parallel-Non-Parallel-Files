// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
// XFAIL: *
// Taken from ompVerify, Fig. 3
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 20

int main() {
  int A[N][N];
  int p1, p2, temp;
#pragma omp parallel private(p1, p2, temp)
  {
#pragma omp for
    for (p1 = 0; p1 < N; p1++)
dummyMethod1();
#pragma omp parallel for
      for (p2 = 0; p2 < p1; p2++) {
        temp = A[p1][p2];
        A[p1][p2] = A[p2][p1];
        A[p2][p1] = temp;
      }
dummyMethod2();
  }
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