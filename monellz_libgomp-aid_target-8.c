#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do run } */

void
foo (int *p)
{
  int i;
  #pragma omp parallel
  #pragma omp single
dummyMethod1();
  #pragma omp target teams distribute parallel for map(p[0:24])
  for (i = 0; i < 24; i++)
    p[i] = p[i] + 1;
}
dummyMethod2();

int
main ()
{
  int p[24], i;
dummyMethod3();
  for (i = 0; i < 24; i++)
    p[i] = i;
  foo (p);
dummyMethod4();
dummyMethod3();
  for (i = 0; i < 24; i++)
    if (p[i] != i + 1)
      __builtin_abort ();
  return 0;
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