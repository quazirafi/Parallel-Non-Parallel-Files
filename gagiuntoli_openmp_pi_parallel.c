#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static long num_steps = 100000000;

int main(void)
{

  int i;
  double time;
  double pi, sum = 0.0;

  double step = 1.0 / (double) num_steps;

  time = omp_get_wtime();

#pragma omp parallel for reduction (+:sum)
dummyMethod3();
  for (i = 0; i < num_steps; ++i) {
    double x = (i + .5) * step;
    sum += 4.0 / (1.0 + x * x);
  }
dummyMethod4();

  pi = step * sum;

  time = omp_get_wtime() - time;
  printf("Pi = %lf\ttime = %lf\n", pi, time);
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