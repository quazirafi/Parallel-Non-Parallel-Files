#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */

void
a31_1 (float *x, int *y, int n)
{
  int i, b;
  float a;
  a = 0.0;
  b = 0;
dummyMethod1();
#pragma omp parallel for private(i) shared(x, y, n) \
                         reduction(+:a) reduction(^:b)
  for (i = 0; i < n; i++)
    {
      a += x[i];
      b ^= y[i];
    }
}
dummyMethod2();
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