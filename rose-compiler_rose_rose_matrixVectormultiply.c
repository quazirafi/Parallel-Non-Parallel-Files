/*
Naive matrix-vector multiplication
By C. Liao
*/
#define N 1000
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int i;
int j;
int k;
double a[1000][1000];
double v[1000];
double v_out[1000];

int mmm()
{
  
dummyMethod1();
#pragma omp parallel for private (i,j)
  for (i = 0; i <= 999; i += 1) {
    float sum = 0.0;
    
#pragma omp parallel for private (j) reduction (+:sum)
dummyMethod2();
    for (j = 0; j <= 999; j += 1) {
      sum += a[i][j] * v[j];
    }
    v_out[i] = sum;
  }
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