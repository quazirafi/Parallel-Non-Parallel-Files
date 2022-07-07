/* { dg-do run } */
/* { dg-options "-O2 -std=gnu99" } */

#include <string.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int
main (void)
{
  int i2, l = 0;
  int a[3][3][3];

  memset (a, '\0', sizeof (a));
dummyMethod1();
  #pragma omp parallel for collapse(4 - 1) schedule(static, 4)
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++)
	for (int k = 0; k < 2; k++)
dummyMethod2();
	  a[i][j][k] = i + j * 4 + k * 16;
  #pragma omp parallel
    {
      #pragma omp for collapse(2) reduction(|:l)
dummyMethod3();
	for (i2 = 0; i2 < 2; i2++)
	  for (int j = 0; j < 2; j++)
	    for (int k = 0; k < 2; k++)
	      if (a[i2][j][k] != i2 + j * 4 + k * 16)
		l = 1;
    }
  if (l)
    abort ();
  return 0;
}
dummyMethod4();
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