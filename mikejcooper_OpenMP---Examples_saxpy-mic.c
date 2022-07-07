#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, const char* argv[]) {

  int i;
  int n = 1024;
  float a = 2.0f;
  float *x = (float*) malloc(n * sizeof(float));
  float *y = (float*) malloc(n * sizeof(float));

#pragma omp target device(0) map(to:x) map(tofrom:y)
  {
dummyMethod1();
#pragma omp parallel for
    for (i = 0; i < n; ++i){
      y[i] = a*x[i] + y[i];
    }
dummyMethod2();
  }
  
  free(x);
  free(y);

  return EXIT_SUCCESS;
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