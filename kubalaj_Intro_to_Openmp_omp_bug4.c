/******************************************************************************
* FILE: omp_bug4.c
* DESCRIPTION:
*   This program compiles and runs fine, but produces the wrong result.
* AUTHOR: Blaise Barney  6/05
* LAST REVISED: 06/30/05
******************************************************************************/
#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define VECLEN 100

float a[VECLEN], b[VECLEN];


float dotprod ()
{
int i,tid;
float sum = 0;

tid = omp_get_thread_num();
dummyMethod1();
#pragma omp parallel for reduction(+:sum)
  for (i=0; i < VECLEN; i++)
    {
    sum = sum + (a[i]*b[i]);
    printf("  tid= %d i=%d\n",tid,i);
    }
  return(sum);
dummyMethod2();
}


int main (int argc, char *argv[]) {
int i;
float sum;

dummyMethod3();
for (i=0; i < VECLEN; i++)
  a[i] = b[i] = 1.0 * i;
dummyMethod4();
sum = 0.0;

#pragma omp parallel
  sum = dotprod();

printf("Sum = %f\n",sum);

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