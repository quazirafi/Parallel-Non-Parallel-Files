#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR middle-end/81768 */
/* { dg-do compile } */

float b[10][15][10];

void
foo (void)
{
  float *i;
dummyMethod1();
#pragma omp target parallel for schedule(static, 32) collapse(3)
  for (i = &b[0][0][0]; i < &b[0][0][10]; i++)
    for (float *j = &b[0][15][0]; j > &b[0][0][0]; j -= 10)
      for (float *k = &b[0][0][10]; k > &b[0][0][0]; --k)
        b[i - &b[0][0][0]][(j - &b[0][0][0]) / 10 - 1][(k - &b[0][0][0]) - 1] -= 3.5;
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