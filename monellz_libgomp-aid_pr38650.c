/* PR c++/38650 */
/* { dg-do run } */

#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int e;

int
main ()
{
  volatile int i, j = 10;
  e = 0;
dummyMethod1();
#pragma omp parallel for reduction(+:e)
  for (i = 0; i < j; i += 1)
    e++;
  if (e != 10)
dummyMethod2();
    abort ();
  e = 0;
dummyMethod1();
#pragma omp parallel for reduction(+:e)
  for (i = 0; i < j; ++i)
    e++;
  if (e != 10)
dummyMethod2();
    abort ();
  e = 0;
dummyMethod1();
#pragma omp parallel for reduction(+:e)
  for (i = 0; i < j; i++)
    e++;
  if (e != 10)
dummyMethod2();
    abort ();
  e = 0;
dummyMethod1();
#pragma omp parallel for reduction(+:e)
  for (i = 0; i < 10; i += 1)
    e++;
  if (e != 10)
dummyMethod2();
    abort ();
  e = 0;
			dummyMethod1();
#pragma omp parallel for reduction(+:e)
  for (i = 0; i < 10; ++i)
    e++;
			dummyMethod2();
  if (e != 10)
    abort ();
  e = 0;
			dummyMethod1();
#pragma omp parallel for reduction(+:e)
  for (i = 0; i < 10; i++)
    e++;
			dummyMethod2();
  if (e != 10)
    abort ();
  return 0;
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