#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */

void bar (int *);

void
foo ()
{
  int i,j;
dummyMethod1();
#pragma omp parallel for ordered(1)
  for (i=0; i < 100; ++i)
    {
#pragma omp ordered depend(sink:i-1)
dummyMethod2();
    bar(&i);
#pragma omp ordered depend(source)
    }
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