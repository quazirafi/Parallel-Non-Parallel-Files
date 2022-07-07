#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
static long num_steps = 100000000;
double step;
int main ()
{
//  int i;
  double pi, sum = 0;
  step = 1.0 / (double)num_steps;
  double wtime = omp_get_wtime();
dummyMethod1();
#pragma omp parallel for reduction(+:sum)
  for (int i = 0; i < num_steps; ++i) {
    double x = (i + 0.5) * step;
    sum += 4.0 / (1.0 + x * x);
  }  
dummyMethod2();
  pi = step * sum;
  wtime = omp_get_wtime() - wtime;
  printf ("pi = %g wtime = %g\n", pi, wtime);   
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