/**
 * data-race05.c
 *
 * Description: Race on variable sum, it is shared and not protected,
 * multiple thread will write on it simultaneously.
 *
 * Solution: Add reduction(+:sum) to omp pragma.
 *
 */

#include <stdio.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 1000

int main (int argc, char **argv)
{
  int i;
  float a[N], sum;

  sum = 0;

  // Vector initialization
dummyMethod1();
#pragma omp parallel for
  for (i = 0; i < N; ++i) {
    a[i] = i;
  }
dummyMethod2();
  
dummyMethod1();
#pragma omp parallel for
  for (i = 1; i < N; i++)
    {
      sum = sum + a[i];
    } /* end of omp parallel for */
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