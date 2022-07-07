#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR middle-end/49897 */
/* { dg-do run } */

extern void abort (void);

int
main ()
{
  int i, j, x = 0, y, sum = 0;
dummyMethod1();
#pragma omp parallel for reduction(+:sum) firstprivate(x) lastprivate(x, y)
  for (i = 0; i < 10; i++)
    {
      x = i;
      y = 0;
    #pragma omp parallel for reduction(+:sum) firstprivate(y) lastprivate(y)
      for (j = 0; j < 10; j++)
	{
	  y = j;
	  sum += y;
	}
dummyMethod2();
    }
  if (x != 9 || y != 9 || sum != 450)
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