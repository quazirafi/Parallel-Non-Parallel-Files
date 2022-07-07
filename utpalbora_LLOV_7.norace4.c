// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define M 20
#define N 20

int main() {
  double data[M][N], mean[N];
dummyMethod1();
#pragma omp parallel for
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++) {
      data[i][j] -= mean[j];
    }
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