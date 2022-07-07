#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR c/27499 */
/* { dg-do compile } */

extern void bar (unsigned int);

void
foo (void)
{
  unsigned int i;
dummyMethod1();
#pragma omp parallel for
  for (i = 0; i < 64; ++i)
    bar (i);
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