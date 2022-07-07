/* A kernel for two level parallelizable loop with reduction */
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
float u[100][100];

float foo()
{
  int i;
  int j;
  float temp;
  float error;
  
dummyMethod1();
#pragma omp parallel for private (temp,i,j) reduction (+:error)
  for (i = 0; i <= 99; i += 1) {
    
#pragma omp parallel for private (temp,j) reduction (+:error)
dummyMethod2();
    for (j = 0; j <= 99; j += 1) {
      temp = u[i][j];
      error = error + temp * temp;
    }
  }
  return error;
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