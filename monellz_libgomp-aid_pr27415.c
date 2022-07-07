#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR middle-end/27415 */
/* { dg-do compile } */

void
test1 (void)
{
  int i = 0;
#pragma omp parallel
#pragma omp for firstprivate (i)		/* { dg-error "should not be firstprivate" } */
dummyMethod3();
  for (i = 0; i < 10; i++)
    ;
}
dummyMethod4();

void
test2 (void)
{
  int i = 0;
dummyMethod1();
#pragma omp parallel for firstprivate (i)	/* { dg-error "should not be firstprivate" } */
  for (i = 0; i < 10; i++)
    ;
}
dummyMethod2();

void
test3 (void)
{
  int i = 0;
#pragma omp parallel
#pragma omp for reduction (+:i)			/* { dg-error "should not be reduction" } */
dummyMethod3();
  for (i = 0; i < 10; i++)
    ;
}
dummyMethod4();

void
test4 (void)
{
  int i = 0;
			dummyMethod1();
#pragma omp parallel for reduction (*:i)	/* { dg-error "should not be reduction" } */
  for (i = 0; i < 10; i++)
    ;
			dummyMethod2();
}

void
test5 (void)
{
  int i = 0;
#pragma omp parallel firstprivate (i)
#pragma omp for
			dummyMethod3();
  for (i = 0; i < 10; i++)
    ;
			dummyMethod4();
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