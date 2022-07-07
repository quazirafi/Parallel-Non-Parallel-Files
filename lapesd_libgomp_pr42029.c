#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR middle-end/42029 */
/* { dg-do run } */

extern void abort (void);

int
main ()
{
  int i;
  _Complex int c = 0;

dummyMethod1();
#pragma omp parallel for private(i) reduction(+:c)
  for (i = 0; i < 8; ++i)
    c += 1;

  if (c != 8)
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