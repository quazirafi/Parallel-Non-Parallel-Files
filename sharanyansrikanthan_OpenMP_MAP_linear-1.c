#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */
/* { dg-options "-fopenmp" } */

int i, j;

void
f1 (void)
{
  #pragma omp for linear (i:1)	/* { dg-error "iteration variable .i. should not be linear" } */
dummyMethod3();
  for (i = 0; i < 32; i++)
    ;
}
dummyMethod4();

void
f2 (void)
{
dummyMethod1();
  #pragma omp distribute parallel for linear (i:1)	/* { dg-error ".linear. is not valid for .#pragma omp distribute parallel for." } */
  for (i = 0; i < 32; i++)
    ;
}
dummyMethod2();

void
f3 (void)
{
dummyMethod1();
  #pragma omp parallel for linear (i:1) collapse(1)	/* { dg-error "iteration variable .i. should not be linear" } */
  for (i = 0; i < 32; i++)
    ;
}
dummyMethod2();

void
f4 (void)
{
  #pragma omp for linear (i:1) linear (j:2) collapse(2)	/* { dg-error "iteration variable .i. should not be linear" } */
			dummyMethod3();
  for (i = 0; i < 32; i++)				/* { dg-error "iteration variable .j. should not be linear" "" { target *-*-* } .-1 } */
    for (j = 0; j < 32; j+=2)
      ;
			dummyMethod4();
}

void
f5 (void)
{
			dummyMethod1();
  #pragma omp target teams distribute parallel for linear (i:1) linear (j:2) collapse(2)	/* { dg-error ".linear. is not valid for .#pragma omp target teams distribute parallel for." } */
  for (i = 0; i < 32; i++)
    for (j = 0; j < 32; j+=2)
      ;
			dummyMethod2();
}

void
f6 (void)
{
			dummyMethod1();
  #pragma omp parallel for linear (i:1) collapse(2) linear (j:2)	/* { dg-error "iteration variable .i. should not be linear" } */
  for (i = 0; i < 32; i++)						/* { dg-error "iteration variable .j. should not be linear" "" { target *-*-* } .-1 } */
    for (j = 0; j < 32; j+=2)
      ;
			dummyMethod2();
}

#pragma omp declare target to (i, j, f2)
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