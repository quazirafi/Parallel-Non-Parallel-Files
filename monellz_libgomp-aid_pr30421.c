#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR middle-end/30421 */
/* { dg-do compile } */
/* { dg-options "-O2 -fopenmp -Wall" } */

int
foo ()
{
  int a = 0, i;

dummyMethod1();
#pragma omp parallel for firstprivate(a) lastprivate(a)
  for (i = 0; i < 10; i++)
    a += i;

  return a;
dummyMethod2();
}

int
bar ()
{
  int a = 0, i;

dummyMethod1();
#pragma omp parallel for firstprivate(a) lastprivate(a) schedule(static, 2)
  for (i = 0; i < 10; i++)
    a += i;

  return a;
dummyMethod2();
}

int
baz ()
{
  int a = 0, i;

			dummyMethod1();
#pragma omp parallel for firstprivate(a) lastprivate(a) schedule(dynamic)
  for (i = 0; i < 10; i++)
    a += i;
			dummyMethod2();

  return a;
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