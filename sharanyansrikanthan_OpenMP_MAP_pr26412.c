#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR middle-end/26412 */
/* { dg-do compile } */

extern double a[];
extern int b;

double
test (void)
{
  int i;
  double c = 0;

dummyMethod1();
#pragma omp parallel for private(i) reduction(+:c)
  for (i = 0; i < 10000; i++)
    c += a[b];

  return c;
dummyMethod2();
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