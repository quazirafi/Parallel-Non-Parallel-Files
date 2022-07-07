#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR middle-end/25989 */
/* { dg-do compile } */
/* { dg-options "-O2 -fopenmp" } */

int
main (void)
{
  int i, j;
  float a, b = 1.0;

dummyMethod1();
#pragma omp parallel for schedule(guided,1) private(j)
  for (i = 1; i <= 9; i++)
    for (j = 1; j <= 9; j++)
      a = b;
  return 0;
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