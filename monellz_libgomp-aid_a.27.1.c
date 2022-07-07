#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */

void
a27 ()
{
  int i, a;
#pragma omp parallel private(a)
  {
dummyMethod1();
#pragma omp parallel for private(a)
    for (i = 0; i < 10; i++)
      {
	/* do work here */
dummyMethod2();
      }
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