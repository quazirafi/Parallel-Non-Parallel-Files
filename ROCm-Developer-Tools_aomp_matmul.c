#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

const int N = 128*2;

int main(int argc, char **argv) {
float matA[N][N];
float matB[N][N];
float matC[N][N];
float matE[N][N];

  fprintf(stderr, "Starting matmul\n");
  #pragma omp target data map(to: matA, matB) map(from: matC) 
  {
    float tmp;
dummyMethod1();
    #pragma omp target teams distribute parallel for private(tmp) map(to:N) //collapse(2)
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        tmp = 0.0;
        for (int k = 0; k < N; k++) {
          tmp += matA[i][k] * matB[k][j];
        }
        matC[i][j] = tmp;
      }
    }
dummyMethod2();
  }
  fprintf(stderr, "Passed\n");
  return 0;
}
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