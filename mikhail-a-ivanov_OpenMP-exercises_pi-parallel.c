#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static long num_steps = 100000000;
double step;
void main ()
 {
 int i;
 double time;
 double x, pi, sum = 0.0;
 time = omp_get_wtime();
 step = 1.0 / (double) num_steps;
dummyMethod1();
 #pragma omp parallel for reduction (+:sum)
  for (i=0; i< num_steps; i++)
  {
  double x = (i+0.5)*step;
dummyMethod2();
   sum = sum + 4.0/(1.0+x*x);
  }
 pi = step * sum;
 time = omp_get_wtime() - time;
 printf("Approximate value of pi is: %f       time = %lf s\n", pi, time);
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