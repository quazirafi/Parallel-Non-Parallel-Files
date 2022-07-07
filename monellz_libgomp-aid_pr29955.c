#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR c/29955 */
/* { dg-do compile } */
/* { dg-options "-O2 -fopenmp -fexceptions" } */

extern void bar (int);

void
foo (int n)
{
  int i;
dummyMethod1();
#pragma omp parallel for schedule(dynamic)
  for (i = 0; i < n; i++)
    bar (0);
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