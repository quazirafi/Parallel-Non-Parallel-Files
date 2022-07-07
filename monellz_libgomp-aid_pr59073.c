#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR c/59073 */
/* { dg-do compile } */
/* { dg-options "-fopenmp" } */

void
foo ()
{
  int i; 
dummyMethod1();
#pragma omp distribute parallel for
  for (i = 0; i < 10; i)	/* { dg-error "invalid increment expression" } */
    ;
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