/* { dg-do run } */

#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void
work (int k)
{
#pragma omp ordered
  printf (" %d\n", k);
}

void
a21 (int lb, int ub, int stride)
{
  int i;
dummyMethod1();
#pragma omp parallel for ordered schedule(dynamic)
  for (i = lb; i < ub; i += stride)
    work (i);
}
dummyMethod2();

int
main ()
{
  a21 (0, 100, 5);
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