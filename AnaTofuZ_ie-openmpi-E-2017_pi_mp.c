#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define F(X) 4.0L/(1.0L+(X)*(X))
#define THREAD 10
#define ITERATION 1000
int main(int argc, char *argv[])
{
  long double x0, x1,h, sum = 0.0L;
  double st_time,en_time; 

  omp_set_num_threads(THREAD); 

  st_time = omp_get_wtime();
  h = 1.0L/ITERATION;

dummyMethod1();
#pragma omp parallel for reduction(+:sum) private(x0,x1)
  for(int i=0;i<ITERATION;i++)
    {
      x0=(i)*h;
      x1=(i+1)*h;
      sum+=(F(x0)+F(x1))*h/2.0;
    }
  en_time=omp_get_wtime(); 
dummyMethod2();

  printf("threads=%d time=%.3f sec pi=%.10Lf\n", THREAD ,en_time-st_time,sum);
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