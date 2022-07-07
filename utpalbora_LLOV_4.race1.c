// RUN: clang %loadLLOV %s -o /dev/null 2>&1 | FileCheck %s
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 4

int main() {
  int A[N][N][N][N][N][N][N][N][N];
dummyMethod1();
#pragma omp parallel for
for (int i = 1; i < N; i++)
  for (int j = 1; j < N; j++)
    for (int k = 1; k < N; k++)
      for (int l = 1; l < N; l++)
        for (int m = 1; m < N; m++)
          for (int n = 1; n < N; n++)
            for (int o = 1; o < N; o++)
              for (int p = 1; p < N; p++)
                for (int q = 1; q < N; q++)
                  A[i][j][k][l][m][n][o][p][q] +=
                      A[i - 1][j][k][l][m][n][o][p][q];
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