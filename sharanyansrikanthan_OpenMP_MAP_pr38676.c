#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR middle-end/38676 */
/* { dg-do compile } */
/* { dg-options "-fopenmp" } */

int
main ()
{
  int bar, foo = 1;
dummyMethod1();
#pragma omp parallel for shared(foo)
  for (bar = 0; bar < 3; bar++)
    {
      switch (foo)
	{
	case 1:
dummyMethod2();
	  break;
	}
    }
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