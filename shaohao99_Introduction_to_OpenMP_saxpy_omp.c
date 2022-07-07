#include <stdio.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
  long long int i, n=50000000;
  float a=2.0;
  float x[n];
  float y[n];
  double start_time, end_time;

dummyMethod1();
#pragma omp parallel for private(i)
  for (i = 0; i < n; i++){
    x[i] = 1.0;
    y[i] = 2.0;
  }
dummyMethod2();

  start_time = omp_get_wtime();
//#pragma omp parallel for schedule(static,100) private(i)
dummyMethod1();
#pragma omp parallel for private(i)
  for (i = 0; i < n; i++){
    y[i] = a*x[i] + y[i];
  }
dummyMethod2();
  end_time = omp_get_wtime();
  printf ("SAXPY Time: %f\n", end_time - start_time);
  
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