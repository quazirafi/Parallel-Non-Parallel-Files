#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR middle-end/49898 */
/* { dg-do run } */

extern void abort (void);

int
main ()
{
  int i, j, sum = 0;
dummyMethod1();
#pragma omp parallel for reduction(+:sum)
  for (i = 0; i < 10; i++)
    #pragma omp parallel for reduction(+:sum)
    for (j = 0; j < 10; j++)
      sum += j;
  if (sum != 450)
dummyMethod2();
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