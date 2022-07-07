#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 1000

void MatMul(float *a, float *b, float *c) {
  #pragma omp target map(to: a[:N*N], b[:N*N]) map(from : c[:N*N]) device(0)
dummyMethod1();
  #pragma omp parallel for
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      c[i * N + j] = 0;
      for (int k = 0; k < N; ++k) {
        c[i * N + j] += a[i * N + k] * b[k * N + j];
      }
    }
  }
dummyMethod2();
}

int main() {
  float *a = (float*) malloc(sizeof(float)*N*N);
  float *b = (float*) malloc(sizeof(float)*N*N);
  float *c = (float*) malloc(sizeof(float)*N*N);
  MatMul(a, b, c);
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