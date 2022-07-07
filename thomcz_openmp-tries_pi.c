#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
static long num_steps = 100000;
double step, pi;

int main() {
  long i;
  double x, sum = 0.0;
  step = 1.0 / (double) num_steps;

dummyMethod1();
  #pragma omp parallel for private(x) reduction(+:sum)
  for (i = 0; i < num_steps; i++) {
    x = (i + 0.5) * step;
    sum = sum + 4.0 / (1.0 + x * x);
  }
dummyMethod2();
  pi = step * sum;
  printf("Pi = %f\n", pi);
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