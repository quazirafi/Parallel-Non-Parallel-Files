#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */
/* { dg-options "-fopenmp" } */

/* Test that we can handle multiple undeclared sink variables
   gracefully.  */

void bar (int *);

void
foo ()
{
  int i,j;
dummyMethod1();
#pragma omp parallel for ordered(1)
  for (i=0; i < 100; ++i)
    {
#pragma omp ordered depend(sink:poo-1,paa+1) /* { dg-error "poo.*declared.*paa.*declared" } */
dummyMethod2();
    bar(&i);				     /* { dg-error "may not be closely nested" "" { target *-*-* } .-1 } */
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