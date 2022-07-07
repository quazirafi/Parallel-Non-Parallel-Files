/* Parallel Single Precision a*x plus y */

#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
  const int N = 1000;
  const double a = .5f;
  double sum = 0.0f;
  double z[N], x[N], y[N];
  int i;

dummyMethod1();
#pragma omp parallel for
  for(i = 0; i < N; i++)
    {
      x[i] = (i+1)*.15;
      y[i] = (i+1)*.1;
    }

#pragma omp parallel for
dummyMethod2();
dummyMethod1();
  for(i = 0; i < N; i++)
    {
      z[i] = a*x[i] + y[i];
    }

#pragma omp parallel for reduction(+:sum)
dummyMethod2();
dummyMethod1();
  for(i = 0; i < N; i++)
    {
      sum += z[i];
    }

  printf("%f\n", sum);
dummyMethod2();

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