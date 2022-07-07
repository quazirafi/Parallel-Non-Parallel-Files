// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 20

int main() {
  int A[N][N];
dummyMethod1();
#pragma omp parallel for schedule(static, 4)
  for (int i = 1; i < N; i++)
    for (int j = 1; j < N; j++)
      A[i][j] = A[i - 1][j - 1];
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