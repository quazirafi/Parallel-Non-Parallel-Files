#include <stdio.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


static long num_steps = 1000000;

double step;

void main() {
  
  int i; 
  double x, pi;
  double sum = 0.0;
  step = 1.0/(double) num_steps;
  clock_t t1, t2;
  t1=clock();
  omp_set_num_threads(4);
dummyMethod1();
#pragma omp parallel for private(x) reduction(+:sum)
  for (i = 0; i < num_steps; i++) {
    x = (i + 0.5)*step;
    sum = sum + 4.0/(1.0 + x*x);
  }
dummyMethod2();
  pi = step * sum;
  t2=clock();
  printf("pi [%lf] step [%lf] sum[%lf]\n", pi, step,sum);
  printf("pi parallel time %f\n", (((float)t2 - (float)t1) / 1000000.0F ) * 1000);
  
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