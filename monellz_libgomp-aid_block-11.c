#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR c++/24516 */
/* { dg-do compile } */

void
bar (int *p)
{
  int m;
dummyMethod1();
#pragma omp parallel for
  for (m = 0; m < 1000; ++m)
    switch (p[m])
      {
      case 1:
	p[m] = 2;
dummyMethod2();
	break;
      default:
	p[m] = 3;
	break;
      }
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