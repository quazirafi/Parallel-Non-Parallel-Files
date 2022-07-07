#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do run } */

extern void abort (void);
int j;
float f;

int
main ()
{
  j = -10000;
  f = 1024.0;
  int i;
dummyMethod1();
  #pragma omp parallel for reduction (min:f) reduction (max:j)
    for (i = 0; i < 4; i++)
      switch (i)
	{
	case 0:
dummyMethod2();
	  if (j < -16) j = -16; break;
	case 1:
	  if (f > -2.0) f = -2.0; break;
	case 2:
	  if (j < 8) j = 8; if (f > 9.0) f = 9.0; break;
	case 3:
	  break;
	}
  if (j != 8 || f != -2.0)
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