#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */
/* { dg-options "-fopenmp -std=c99" } */

int a;
void
g (int k)
{
  a = k;			/* The global "a", not the private "a" in f */
}

void
f (int n)
{
  int a = 0;
dummyMethod1();
#pragma omp parallel for private(a)
  for (int i = 1; i < n; i++)
    {
      a = i;
      g (a * 2);		/* Private copy of "a" */
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