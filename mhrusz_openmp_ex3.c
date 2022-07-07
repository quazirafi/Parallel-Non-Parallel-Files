#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static long num_steps = 100000;
double step;

int main()
{
  double pi, sum;
  double x;
  int i, ts_num;
  step = 1.0/(double)num_steps;
  double start = omp_get_wtime();
dummyMethod1();
  #pragma omp parallel for reduction(+:sum)
  for(i=0;i < num_steps;i++)
  {
    x = (i+0.5)*step;
    sum += 4.0/(1.0+x*x);
  }
dummyMethod2();
  // end of OMP PARALLEL
  printf("%f", omp_get_wtime()-start);

  pi = sum*step;
  printf("pi is %f\n", pi);
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