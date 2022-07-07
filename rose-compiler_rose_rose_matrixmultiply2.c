/*
Naive matrix-matrix multiplication(mmm)
By C. Liao
*/
#define N 1000
#define M 1000
#define K 1000
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int i;
int j;
int k;
double a[1000][1000];
double b[1000][1000];
double c[1000][1000];

int mmm()
{
//#pragma omp parallel for private(i,j,k) shared(a,b,c)
  
dummyMethod1();
#pragma omp parallel for private (i,j,k)
  for (i = 0; i <= 999; i += 1) {
    for (k = 0; k <= 999; k += 1) {
      
#pragma omp parallel for private (j)
dummyMethod2();
      for (j = 0; j <= 999; j += 1) {
        c[i][j] = c[i][j] + a[i][k] * b[k][j];
      }
    }
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