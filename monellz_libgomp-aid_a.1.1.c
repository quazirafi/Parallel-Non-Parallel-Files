#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */

void
a1 (int n, float *a, float *b)
{
  int i;
dummyMethod1();
#pragma omp parallel for
  for (i = 1; i < n; i++)	/* i is private by default */
    b[i] = (a[i] + a[i - 1]) / 2.0;
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